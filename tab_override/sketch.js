function setup() {
	noCanvas();

	let r = floor(random(10));
	let image = createImg(r + '.jpg');
	image.size(windowWidth, windowHeight);
	image.position(0, 0);
}
