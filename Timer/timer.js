var counter = 0;        //global variable
var left_time = 10;     //default


function convertTime(t) {
    let min = floor(t / 60);
    let sec = t % 60;
    return nf(min, 2) + ' : ' + nf(sec, 2);     //nf: number-format
}

var ding;
function preload() {
    ding = loadSound("ding.mp3");
}

function setup() {
    noCanvas();

    var params = getURLParams();
    //console.log(params);                          //set timer in querybox ?min=<minutes>
    if (params.min) {
        var min = params.min;
        left_time = min * 60;
    }

    var timer = select('#time');    //select the <p> tag by its id
    timer.html(convertTime(left_time - counter));

    var interval = setInterval(setTime, 1000);

    function setTime() {
        counter += 1;
        timer.html(convertTime(left_time - counter));
        if (counter === left_time) {
            clearInterval(interval);
            ding.play();
        }
    }
}
