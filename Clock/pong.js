function setup() {
    createCanvas(400, 400);
    angleMode(DEGREES);
}

function draw() {
    background(51);
    let hr = hour();
    let min = minute();
    let sec = second();
    translate(200, 200);
    rotate(-90);

    strokeWeight(8);
    stroke(255, 100, 150);
    noFill();
    let m1 = map(sec, 0, 60, 0, 360);
    arc(0, 0, 300, 300, 0, m1);

    stroke(150, 100, 255);
    let m2 = map(min, 0, 60, 0, 360);
    arc(0, 0, 280, 280, 0, m2);

    stroke(125);
    let m3 = map(hr % 12, 0, 12, 0, 360);
    arc(0, 0, 260, 260, 0, m3);

    push();
    rotate(m1);
    stroke(255, 100, 150);
    line(0, 0, 100, 0);
    pop();

    push();
    rotate(m2);
    stroke(150, 100, 255);
    line(0, 0, 100, 0);
    pop();

    push();
    rotate(m3);
    stroke(125);
    line(0, 0, 100, 0);
    pop();

}
