(function($) {
    "use strict";
	
	
	/**
	 * Magnific Popup
	 */
	$('.magnific').each(function() {
        $(this).magnificPopup({
            delegate: 'a',
            type: 'image',
            gallery: { enabled: true }
        });
    });


    /**
     * Contact Form
     */

    var contact__form__validate

    $('form.contacts').validator().on('submit', function(e) {

        contact__form__validate = $(this);

        if (e.isDefaultPrevented()) {

            alert('Please fill out the Contact Form');

        } else {

            $('#loader').fadeIn();

            $.ajax({
                url: $(this).attr('action'),
                method: 'post',
                data: $(this).serialize()
            }).done(function(retrieve) {

                $('#loader').fadeOut();

                if (retrieve == "Your message was sent!") {

                    contact__form__validate.find('.response.success').fadeIn();

                } else {

                    contact__form__validate.find('.response.error').fadeIn();

                }

                setTimeout(function() {
                    contact__form__validate.find('.response').fadeOut()
                }, 5000)

            })

        }

        return false;

    })

	
})(window.jQuery);