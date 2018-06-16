console.log("Chrome extension go?");

window.addEventListener('mouseup', wordSelected);

function wordSelected() {
  let selectedText = window.getSelection().toString();
  console.log(selectedText);
  if (selectedText.length > 0) {
    let message = {
      text: selectedText
    };
    chrome.runtime.sendMessage(message);
  }
}