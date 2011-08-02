var Photo = {

	upload: function() {
		$('loading').show();
		$('photo_upload').submit();
	},

	finish: function(url) {
		new Ajax.Updater('photos', url, {method:'get', onComplete:function(){
			$('loading').hide();
			$('photo_upload').reset();
		}});
	},

	show: function(url) {
		$('photo').src = url;
		$('mask').show();
		$('photo-wrapper').visualEffect('appear', {duration:0.5});
	},

	hide: function() {
		$('mask').hide();
		$('photo-wrapper').visualEffect('fade', {duration:0.5});
	},

	currentIndex: function() {
		return this.urls().indexOf($('photo').src);
	},

	prev: function() {
		if(this.urls()[this.currentIndex()-1]) {
			this.show(this.urls()[this.currentIndex()-1])
		}
	},

	next: function() {
		if(this.urls()[this.currentIndex()+1]) {
			this.show(this.urls()[this.currentIndex()+1])
		}
	},

	urls: function() {
    if (!this.cached_urls) {
			this.cached_urls = $$('a.show').collect(function(el){
				return el.onclick.toString().match(/".*"/g)[0].replace(/"/g,'');
			});
		}
		return this.cached_urls;
	}

}
