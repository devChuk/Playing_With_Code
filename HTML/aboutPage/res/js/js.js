(function ($) {

$(document).ready(function () {





function loaded() {
  // Define our variables
  var docBody  = document.body,
      anchors  = document.getElementsByTagName('a');

  // Add loaded class to body
  docBody.className += ' loaded';

  // For each link
  for (var i = 0; i < anchors.length; i++) {
    
    // Click function
    anchors[i].onclick = function(e) { 
     
      // Cache our anchor
      var el = this;
     
      // Stop default action
      e.preventDefault();
     
      // Fade out body
      fadeOut(150, docBody);      
      
      // Change page after fade out
      setTimeout( function() { location = el.href }, 150 );
    }
  }
}

/* 
 * Lazy Line Painter - Path Object 
 * Generated using 'SVG to Lazy Line Converter'
 * 
 * http://lazylinepainter.info 
 * Copyright 2013, Cam O'Connell  
 *  
 */ 
 
var pathObj = {
    "logo1": {
        "strokepath": [
            {
                "path": "M 46.5,17. L 25.59,5.5 3.5,18.254 3.5,43.76   25.59,56.514 46.5,43.672 46.5,31.5 25.305,18.836 14.742,24.908 35.867,37.052 25.305,43.122 14.742,37.052 ",
                "duration": 1200
            }
        ],
        "dimensions": {
            "width": 50,
            "height": 60
        }
    }
}; 
 
 
 $('#logo1').lazylinepainter( 
 {
    "svgData": pathObj,
    "strokeWidth": 1.5,
    "delay": 1000,
    "strokeColor": "#000"
}).lazylinepainter('paint'); 



 
 
 $('.icon-mousedown2').transition({
            opacity: '1',
            y: 0,
            delay: 2000
        }, 2000);


$('#page').transition({
            opacity: '1',
            delay: 300
        }, 2000, 'snap');

var $bio = $('#bio');
var $bioexpand = $('#bioexpand');


$bio.click(function (e) {
    e.preventDefault();
    var $bioexpand = $('#bioexpand');
    if ($bioexpand.css('opacity') == 0) {
        $bioexpand.slideDown(400).transition({ opacity: 1.0, top:0 });
        $bio.html('hide about');
    } else {
        $bioexpand.transition({ opacity: 0.0, top:10 }).slideUp(400);
        $bio.html('about');
    }
});

		$('.followme').fixTo('#content');
        $("#video").fitVids();
        $('#logo').transition({
            perspective: '100px',
            rotateY: '0deg',
            delay: 800
        }, 2000, 'snap');
    });

    $(function () {
        $(".logoinner")
            .mouseenter(function () {
            $(this).children().css({
                'opacity': '0.5'
            });
        })
            .mouseleave(function () {
            $(this).children().css({
                'opacity': '1'
            });
        });
    });

    // if (typeof String.prototype.trim !== 'function') {
    //     String.prototype.trim = function () {
    //         return this.replace(/^\s+|\s+$/g, '');
    //     };
    // }

        $('#heroburrito .vert:not(".home") h1').attr('data-originalText', function () {

        return (this.textContent || this.innerText).trim();

    }).hover(function () {
        var speed = 200;
        $(this).fadeOut(speed, function () {
            /* â† */
            $('a.homehover', this).text('return').append('<i class="homeicon">h</i>');
            $(this).fadeIn(speed).addClass('home');
        });
    },

    function () {
        var speed = 0;
        $(this).fadeOut(speed, function () {
            $('a.homehover', this).text($(this).attr('data-originalText'));
            $(this).fadeIn(speed).removeClass('home');
        });
    });


    function hero() {
        var hero = $('#heroburrito'); /*hero var */
        var menu = $('#masthead'); /*menu var */
        var windowheight = $(window).height();
        var menuheight = $(menu).height();
        var calculatedheight = windowheight - menuheight
        $(hero).css({
            'height': windowheight
        });
    }

        $(window).load(function () {
        hero();
        

        if (!(/Android|iPhone|iPad|iPod|BlackBerry|Windows Phone/i).test(navigator.userAgent || navigator.vendor || window.opera)) {
            var s = skrollr.init({
                forceHeight: false,
                smoothScrolling: true
            });
        }

        // This uses the Hotkeys jQuery plugin. See below for
        // the native jQuery alternative.
        $(document).keyup(function (event) {
            var url = false;
            if (event.which == 37) {
                url = $('.nav-previous a').attr('href');
            }
            if (event.which == 39) {
                url = $('.nav-next a').attr('href');
            }
            if (event.which == 72) {
                url = $('a.home').attr('href');
            }
            if (url) {
                window.location = url;
            }
        });

        $(document).keydown(function (event) {
            if (event.which == 37) {
                $('#keys .key.left').addClass('activekey');
            }
            if (event.which == 39) {
                $('#keys .key.right').addClass('activekey');
            }
        });


        $('#heroburrito .vert.home h1').transition({
            perspective: '1000px',
            rotateX: '0',
            y: '0px',
            opacity: '1',
            delay: '400'
        }, 500, 'snap');
        $('#heroburrito .vert h1').transition({
            perspective: '1000px',
            rotateX: '0',
            y: '0px',
            opacity: '1',
            delay: '400'
        }, 500, 'snap');
    });




    $(window).resize(function () {
        hero();

    });


		function is_touch_device() {
		  return !!('ontouchstart' in window) // works on most browsers 
		      || !!('onmsgesturechange' in window); // works on ie10
		};

        if(is_touch_device()) {
        	var item = $('.item');
        	var thumbnail = $('.thumbnail');
        	$(item).addClass('hoverstate');
        	$(thumbnail).css('opacity','0.5');
		}

        function hover() {
        var item = $('.item');
        var thumbnail = $('.thumbnail');
        var hover = $('.hover');

        $(item).hover(function () {
        

		
            $(this).addClass('hoverstate');
            $(this).find('.thumbnail').transition({
                opacity: '0.2'
            }, 500);

        }, function () {
            $(this).removeClass('hoverstate');
            $(this).find('.thumbnail').transition({
                opacity: '1'
            }, 300);
        });
    }
    hover();
    
})(jQuery);