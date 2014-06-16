$(function() {
        $('.swapper').click(button_swap);
      });

/* Double button swap function */

var button_swap = function() {
	if ($(this).prev().hasClass('active')) {
		// On fait apparaître le bouton caché
		$('.inactive').addClass('active');
		$('.inactive').removeClass('inactive');
		$(this).addClass('inactive');
		$(this).removeClass('active');
		$(this).prev().addClass('inactive');
		$(this).prev().removeClass('active');
	};
	if ($(this).hasClass('search') || $(this).hasClass('lucky')) {
		search_swap();
	}
}

/* Search swap function */

var search_swap = function() {
	if ($(this).hasClass('search')) {
		$('#search-inputs').attr('action', '/search');
        $('.level').toggle();
	} else {
		$('#search-inputs').attr('action', '/lucky');
        $('.level').toggle();
	}
}