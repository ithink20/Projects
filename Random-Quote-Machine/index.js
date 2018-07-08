$(document).ready(function(){
    var randomQuote;
    var randomAuthor;
    var random;
    function getQuote() {
        var quotes = ["Spread Love everywhere you go.", "Whatever you do, do it well.", "You are enough just as you are.", "You get what you give."];
        var authors = ["Mother Teresa", "Walt Disney", "Meghan Markle", "Jennifer Lopez"];

        random = Math.floor(Math.random()*quotes.length);
        randomQuote = quotes[random];
        randomAuthor = authors[random];

        $(".quote").text(randomQuote);
        $(".author").text(randomAuthor);
    }
    $("#tweet-quote").on("click", function() {
        window.open("https://twitter.com/intent/tweet?text="+randomQuote+"    -" + randomAuthor);
    });
    $("#new-quote").on("click", function() {
        getQuote();
    });
});
