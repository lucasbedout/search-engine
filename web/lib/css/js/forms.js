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
}

