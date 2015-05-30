module.exports = function(grunt) {

	// Project configuration.
	grunt.initConfig({
		pkg: grunt.file.readJSON('package.json'),

		uglify: {
			build: {
				src: ['js/*.js', '!js/main.min.js'],
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

	// plugin tasks
	grunt.loadNpmTasks('grunt-contrib-concat');
	grunt.loadNpmTasks('grunt-contrib-uglify');
	grunt.loadNpmTasks('grunt-jekyll');
	grunt.loadNpmTasks('grunt-sftp-deploy');

	// Default task(s).
	grunt.registerTask('default', [
		'uglify',
		'jekyll:build',
		'sftp-deploy'
	]);

};
