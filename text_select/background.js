console.log('background running');

chrome.runtime.onMessage.addListener(receiver);

window.word = "";

function receiver(request, sender, sendResponse) {
  console.log(request);
  window.word = request.text;
}