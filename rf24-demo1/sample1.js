/*
var rf24js = require('rf24js');
var radio = rf24js.radio;
var PALevel = rf24js.PALevel;
var CRCLength = rf24js.CRCLength;
var Datarate = rf24js.Datarate;

var radioNumber = 0;

//0xABCDABCD71, 0x544d52687C
var addr0 = Buffer.from([0xAB, 0xCD, 0xAB, 0xCD, 0x71]);
var addr1 = Buffer.from([0x54, 0x4d, 0x52, 0x68, 0x7C]);

console.log(radio)

function setup() {
  console.log("rf24 setup");

  // Setup and configure rf radio
  radio.create(2, 10);
  radio.begin();

  // optionally, increase the delay between retries & # of retries
  radio.setRetries(15, 15);

  // Dump the configuration of the rf unit for debugging
  radio.printDetails();

  if (radioNumber == 0) {
    radio.openWritingPipe(addr1);
    radio.openReadingPipe(1, addr0);
  } else {
    radio.openWritingPipe(addr0);
    radio.openReadingPipe(1, addr1);
  }

  radio.startListening();
  loop();
}
*/

var outText = "0";
var textSent = false;

function main() {
  generateOutText();
  loop();
}

function loop(){
  console.log("loop timestamp: ", new Date().getTime());
  
  if(textSent != true) {
    console.log("loop sending text: ", outText);
    textSent = true;
  }
  
  //setImmediate(loop, {});
  setTimeout(loop, 100, {});
}

function generateOutText() {
  if(textSent == false) {
    setTimeout(generateOutText, 100, {});
    return;
  }
  outText = new Date().getTime().toString();
  textSent = false;
  setTimeout(generateOutText, 1000, {});
}

main();