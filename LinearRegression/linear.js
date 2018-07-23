// y = mx + c       linear line.
// Formula:
// m = (sum(x - xmean)(y - ymean)) / sum(x - xmean)^2;
// c = ymean - m * xmean;




var data_points = [];
var m = 1;
var c = 0;
function setup() {
    createCanvas(400, 400);
}

function draw() {
    background(51);

    for (var i = 0; i < data_points.length; ++i) {
        var x = map(data_points[i].x, 0, 1, 0, width);
        var y = map(data_points[i].y, 0, 1, height, 0);
        fill(255);
        stroke(255);
        ellipse(x, y, 8, 8);
    }
    if (data_points.length > 1) {
        linearRegression();
        drawLine();
    }
}

function linearRegression() {
    var x_sum = 0, y_sum = 0;
    for (let i = 0; i < data_points.length; ++i) {
        x_sum += data_points[i].x;
        y_sum += data_points[i].y;
    }
    var xmean = x_sum / data_points.length;
    var ymean = y_sum / data_points.length;
    var numerator = 0, denominator = 0;
    for (let i = 0; i < data_points.length; ++i) {
        var x = data_points[i].x - xmean;
        var y = data_points[i].y - ymean;
        numerator += (x - xmean) * (y - ymean);
        denominator += (x - xmean) * (x - xmean);
    }
    m = numerator / denominator;
    c = ymean - m * xmean;
}

function drawLine() {
    var x1 = 0;
    var y1 = m * x1 + c;
    var x2 = 1;
    var y2 = m * x2 + c;

    x1 = map(x1, 0, 1, 0, width);
    y1 = map(y1, 0, 1, height, 0);
    x2 = map(x2, 0, 1, 0, width);
    y2 = map(y2, 0, 1, height, 0);


    stroke(255, 100, 100);
    line(x1, y1, x2, y2);
}

function mousePressed() {
    var x = map(mouseX, 0, width, 0, 1);
    var y = map(mouseY, 0, height, 1, 0);

    var point = createVector(x, y);
     data_points.push(point);
}
