var serialport = require('serialport');
var SerialPort = serialport.SerialPort;

var port = new SerialPort('/dev/ttyACM0', {
  parser: serialport.parsers.readline('\n')
});

port.on('data', function (data) {
  console.log('Data: ' + data);
  console.log(Date());
});