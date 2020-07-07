$(document).ready(function () {
    //Initialize tooltips
    $('.nav-tabs > li a[title]').tooltip();
    
    //Wizard
    $('a[data-toggle="tab"]').on('show.bs.tab', function (e) {

        var $target = $(e.target);
    
        if ($target.parent().hasClass('disabled')) {
            return false;
        }
    });

    $(".next-step").click(function (e) {
		if ($("#txt_nombre") && $("#txt_app_p") && $("#txt_app_m") && $("#txt_foto") && $("#txt_usuario") && $("#txt_psw").val()!="") { 
			e.preventDefault();
			var $active = $('.board .nav-tabs li.active');
			$active.next().removeClass('disabled');
			nextTab($active);
		  }
    });
	 $(".next-step-contacto").click(function (e) {
		if ($("#txt_email").val()!="") {
			e.preventDefault();
			var $active = $('.board .nav-tabs li.active');
			$active.next().removeClass('disabled');
			nextTab($active);
		  }
    });
	 $(".next-step-organismo").click(function (e) {
		if ($("#txt_organismos") && $("#txt_uni_respon").val()!="") {
			e.preventDefault();
			var $active = $('.board .nav-tabs li.active');
			$active.next().removeClass('disabled');
			nextTab($active);
		  }
    });
    $(".prev-step").click(function (e) {

        var $active = $('.board .nav-tabs li.active');
        prevTab($active);

    });
});

function nextTab(elem) {
    $(elem).next().find('a[data-toggle="tab"]').click();
}
function prevTab(elem) {
    $(elem).prev().find('a[data-toggle="tab"]').click();
}


//according menu

$(document).ready(function()
{
    //Add Inactive Class To All Accordion Headers
	$('.accordion-header').toggleClass('inactive-header');
	
	//Set The Accordion Content Width
	var contentwidth = $('.accordion-header').width();
	$('.accordion-content').css({});
	
	//Open The First Accordion Section When Page Loads
	$('.accordion-header').first().toggleClass('active-header').toggleClass('inactive-header');
	$('.accordion-content').first().slideDown().toggleClass('open-content');
	
	// The Accordion Effect
	$('.accordion-header').click(function () {
		if($(this).is('.inactive-header')) {
			$('.active-header').toggleClass('active-header').toggleClass('inactive-header').next().slideToggle().toggleClass('open-content');
			$(this).toggleClass('active-header').toggleClass('inactive-header');
			$(this).next().slideToggle().toggleClass('open-content');
		}
		
		else {
			$(this).toggleClass('active-header').toggleClass('inactive-header');
			$(this).next().slideToggle().toggleClass('open-content');
		}
	});
	
	return false;
});