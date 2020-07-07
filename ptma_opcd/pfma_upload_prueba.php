<html>
  
<head>  
  
<link href="https://raw.githubusercontent.com/enyo/dropzone/master/dist/dropzone.css" type="text/css" rel="stylesheet" />
  
<!-- 1 -->
<script src="//ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js"></script>
 
<script src="dropzone.min.js"></script>
 
<script>
Dropzone.options.myDropzone = {

  // Prevents Dropzone from uploading dropped files immediately
  acceptedFiles: '*.zip',
  autoProcessQueue: false,

  init: function() {
    var submitButton = document.querySelector("#submit-all")
        myDropzone = this; // closure

            submitButton.addEventListener("click", function() {
              console.log ('dentro del Dropzone/click');  
              myDropzone.processQueue(); // Tell Dropzone to process all queued files.
            });

    // You might want to show the submit button only when 
    // files are dropped here:
            this.on("addedfile", function(file) {
              // Show submit button here and/or inform user to click it.
             console.log ('addedfile');   
               console.log ('addedfile/archivo error' + file.name);   
              console.log ('addedfile/ Typo >' + file.type + '<');   
            }); // fin de this.on

      // Using a closure.
      var _this = this;

      // Setup the observer for the button.
      document.querySelector("button#clear-dropzone").addEventListener("click", function() {
        // Using "_this" here, because "this" doesn't point to the dropzone anymore
        _this.removeAllFiles();
        // If you want to cancel uploads as well, you
        // could also call _this.removeAllFiles(true);
      });

        this.on("processing", function(file) {
              console.log ('procesanso');   
        });

        this.on("error", function(file) {
              console.log ('archivo error' + file.name);   
              console.log ('Typo >' + file.type + '<');   
              alert('Por favor ingrese archivos comprimidos');
              _this.removeFile(file);
        });


  
    } // fin de init: function

}; // fin de Dropzone.options.myDropzone
</script>
</head>
<body>
<!-- 2 -->
<button id="submit-all">Submit all files</button>
<button id="clear-dropzone">Clear Dropzone</button>

<form action="upload.php" class="dropzone dropzone-previews" id="my-dropzone"></form>
</body>
</html>
