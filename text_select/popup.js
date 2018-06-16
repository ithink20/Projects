function setup() {
  noCanvas();

  let bgpage = chrome.extension.getBackgroundPage();
  let word = bgpage.word;
  createP(word);
}