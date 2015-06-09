var page = require('webpage').create();

page.onResourceRequested = function(request) {
  console.log('Request ' + JSON.stringify(request, undefined, 4));
};
page.onResourceReceived = function(response) {
  console.log('Receive ' + JSON.stringify(response, undefined, 4));
};
page.onError = function (msg, trace) {
  console.log(msg);
  trace.forEach(function(item) {
      console.log('  ', item.file, ':', item.line);
  });
};

page.open('http://localhost:8000', function(status) {
  console.log("Status: " + status);
  if(status === "success") {
    page.render('example.png');
  }
  phantom.exit();
});