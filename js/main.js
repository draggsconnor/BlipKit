$(function () {

	$(".nav-button").click(function () {
		$(this).parents(".page-nav").toggleClass("open");
	});

	var soundInstances = {};

	$(".player[href]").click(function (e) {
		e.preventDefault();

		var $this   = $(this);
		var href    = $this.attr("href");
		var volume  = parseFloat($this.data("volume") || 0.5);
		var soundid = $this.data("soundid");
		var state   = $this.data("state") || "";
		var instance;

		if (state == "playing") {
			instance = soundInstances[soundid];
			instance.stop();
			complete();
			return;
		}
		else if (state != "") {
			return;
		}

		function loading() {
			$this.data("state", "loading");
			$this.addClass("loading");
		}

		function play() {
			$this.data("state", "playing");
			$this.removeClass("loading").addClass("playing");
		}

		function complete() {
			$this.data("state", "");
			$this.removeClass("playing");
		}

		function error() {
			$this.data("state", "error");
			$this.removeClass("loading").addClass("error");
		}

		if (!soundid) {
			soundid = "sound" + (new Date()).getTime() + parseInt(Math.random() * 1000);
			$this.data("soundid", soundid);
		}

		if (soundInstances[soundid]) {
			instance = soundInstances[soundid];
			instance.play("sound", {volume: volume});
			play();
		}
		else {
			var queue = new createjs.LoadQueue();
			queue.installPlugin(createjs.Sound);

			queue.addEventListener("fileload", function(e) {
				instance = createjs.Sound.play(soundid, {volume: volume});
				soundInstances[soundid] = instance;

				instance.addEventListener("complete", function(e) {
					complete();
				});

				play();
			});

			queue.addEventListener("error", function(e) {
				error();
			});

			queue.loadManifest([
				{id: soundid, src: href}
			], true);

			loading();
		}
	});

});
