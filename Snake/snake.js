var w = 10;
var s, food;

function setup() {
    var cnv = createCanvas(600, 600);
    let x = (windowWidth - width) / 2;
	let y = (windowHeight - height) / 2;
    cnv.position(x, y);
    s = new Snake();
    frameRate(10);
    foodLocation();
}

function draw() {
    background(51);
    scoreBoard();
    s.end();
    s.update();
    s.show();
    if (s.eat(food)) {
        foodLocation();
    }
    fill(255, 0, 200);
    rect(food.x, food.y, w, w);
}

function keyPressed() {
    if (keyCode === UP_ARROW) {
        s.pos(0, -1);
    } else if (keyCode === LEFT_ARROW) {
        s.pos(-1, 0);
    } else if (keyCode === DOWN_ARROW) {
        s.pos(0, 1);
    } else if (keyCode === RIGHT_ARROW) {
        s.pos(1, 0);
    }
}


function foodLocation() {
    var cols = floor(600/w);
    var rows = floor(560/w);
    food = createVector(floor(random(cols)), floor(random(rows)));
    food.mult(w);
}

function scoreBoard() {
    fill(125);
    rect(0, 560, 600, 40);
    fill(0);
    textFont("Courier");
    textSize(19);
    text("Score : ", 10, 585);
    text("HighScore : ", 400, 585);
    text(s.score, 100, 585);
    text(s.highscore, 540, 585);
}

//snake
function Snake() {
    this.x = 0;
    this.y = 0;
    this.xspeed = 1;
    this.yspeed = 0;
    this.tail = [];
    this.total = 0;
    this.score = 0;
    this.highscore = 0;

    this.update = function() {
        for (let i = 0; i < this.tail.length - 1; ++i) {
            this.tail[i] = this.tail[i + 1];
        }
        if (this.total >= 1) {
            this.tail[this.total - 1] = createVector(this.x, this.y);
        }

        this.x = this.x + this.xspeed * w;
        this.y = this.y + this.yspeed * w;

        this.x = constrain(this.x, 0, 600 - w);
        this.y = constrain(this.y, 0, 560 - w);
    }

    this.eat = function(pos) {
        var d = dist(this.x, this.y, pos.x, pos.y);
        if (d < 1) {
            this.total += 1;
            this.score += 1;
            text(this.score, 70, 625);
            if (this.score > this.highscore) {
                this.highscore = this.score;
            }
            text(this.highscore, 540, 625);
            return true;
        } else {
            return false;
        }
    }

    this.end = function() {
        for (let i = 0; i < this.tail.length; ++i) {
            var pos = this.tail[i];
            var d = dist(this.x, this.y, pos.x, pos.y);
            if (d < 1) {
                gameOver();
                this.total = 0;
                this.score = 0;
                this.tail = [];
            }
        }
    }

    this.pos = function(x, y) {
        this.xspeed = x;
        this.yspeed = y;
    }

    this.show = function() {
        fill(245);
        for (let i = 0; i < this.tail.length; ++i) {
            rect(this.tail[i].x, this.tail[i].y, w, w);
        }
        rect(this.x, this.y, w, w);
    }
}

function gameOver(score) {
    noLoop();
    textSize(40);
    text("Game Over!", (width - 200) / 2, (height - 100) / 2);
}
