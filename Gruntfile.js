module.exports = function(grunt) {

	grunt.initConfig({
		pkg: grunt.file.readJSON('package.json'),

		uglify: {
			build: {
				src: ['bower_components/u.js/dist/u.js', 'bower_components/u.js/dist/u.ie9.js', 'js/*.js', '!js/main.min.js'],
				dest: 'js/main.min.js'
			}
		},

		jekyll: {
			build: {
				options: {
				}
			},
			server: {
				options: {
					serve: true,
					watch: true
				}
			},
		},

		dataUri: {
			dist: {
				src: ['_site/css/*.css'],
				dest: '_site/css',
				options: {
					target: ['_site/css/img/*.*'],
					fixDirLevel: true,
					maxBytes : 2048
				}
			}
		},

		'sftp-deploy': {
			build: {
				auth: {
					host: 'blipkit.audio',
					port: 2121,
					authKey: 'monoxid'
				},
				src: '_site',
				dest: '/domains/blipkit.audio',
				exclusions: ['_site/**/.DS_Store', '_site/**/Thumbs.db'],
				forceVerbose: true
			}
		}
	});

	grunt.loadNpmTasks('grunt-data-uri');
	grunt.loadNpmTasks('grunt-contrib-concat');
	grunt.loadNpmTasks('grunt-contrib-uglify');
	grunt.loadNpmTasks('grunt-jekyll');
	grunt.loadNpmTasks('grunt-sftp-deploy');

	grunt.registerTask('build', [
		'uglify',
		'jekyll:build',
		'dataUri'
	]);

	grunt.registerTask('server', [
		'build',
		'jekyll:server'
	]);

	grunt.registerTask('deploy', [
		'build',
		'sftp-deploy'
	]);

};
