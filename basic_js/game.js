var randomNumber = Math.floor(Math.random() * 100) + 1;

var guesses = document.querySelector('.guesses');
var lastResult = document.querySelector('.lastResult');
var loworHi = document.querySelector('.loworHi');

var guessSubmit = document.querySelector('.guessSubmit');
var guessField = document.querySelector('.guessField');

var guessCount = 1;
var resetButton;
guessField.focus();

function checkGuess() {
	var userGuess = guessField.value;
	if (guessCount === 1) {
		guesses.textContent = 'Previous Guesses : ';
	}
	guesses.textContent += userGuess + ' ';

	if (userGuess === randomNumber) {
		lastResult.textContent = 'Hey! You got it right.';
		lastResult.style.backgroundColor = 'white';
		loworHi.textContent = '';

		setGameOver();
	} else if (guessCount === 10) {
		lastResult.textContent = '!!GAME OVER!!';
		setGameOver();
	} else {
		lastResult.textContent = 'Wrong';
		lastResult.style.backgroundColor = 'red';
		if (userGuess < randomNumber) {
			lastResult.textContent = 'Last Guess was too low!';
		} else if (userGuess > randomNumber) {
			lastResult.textContent = 'Last Guess was too high!';
		}
	}
	guessCount++;
	guessField.value = '';
	guessField.focus();
}

guessSubmit.addEventListener('onclick', checkGuess);

function setGameOver() {
	guessField.disabled = true;
	guessSubmit.disabled = true;
	resetButton = document.createElement('button');
	resetButton.textContent = 'New Game?';
	document.body.appendChild(resetButton);
	resetButton.addEventListener('click', resetGame);
}

function resetGame() {
	guessCount = 1;

	var resetParas = document.querySelectorAll('.resultParas p');
	for (var i = 0 ; i < resetParas.length ; i++) {
		resetParas[i].textContent = '';
	}

	resetButton.parentNode.removeChild(resetButton);

	guessField.disabled = false;
	guessSubmit.disabled = false;
	guessField.value = '';
	guessField.focus();

	lastResult.style.backgroundColor = 'white';

	randomNumber = Math.floor(Math.random() * 100) + 1;
}