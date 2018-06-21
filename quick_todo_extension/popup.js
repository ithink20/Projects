window.onload = function() {
	var data = (localStorage.getItem('todoList')) ? JSON.parse(localStorage.getItem('todoList')) : {
		todo: []
	};

	// remove icon in svg format
	var removeSVG = '<svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" version="1.1" id="Layer_1" x="0px" y="0px" viewBox="0 0 512 512" style="enable-background:new 0 0 512 512;" xml:space="preserve" width="512px" height="512px"><g><g><path d="M394.667,42.667h-57.408l-6.613-13.184C321.557,11.285,303.275,0,282.944,0h-53.909    c-20.331,0-38.592,11.285-47.701,29.483l-6.592,13.184h-57.408C87.915,42.667,64,66.603,64,96v21.333    C64,123.221,68.779,128,74.667,128h362.667c5.888,0,10.667-4.779,10.667-10.667V96C448,66.603,424.085,42.667,394.667,42.667z     M426.667,106.667H85.333V96c0-17.643,14.357-32,32-32h64c4.032,0,7.723-2.283,9.536-5.888l9.557-19.093    c5.44-10.901,16.405-17.685,28.629-17.685h53.909c12.203,0,23.168,6.784,28.629,17.685l9.536,19.093    c1.813,3.605,5.504,5.888,9.536,5.888h64c17.643,0,32,14.357,32,32V106.667z" fill="#32c79d"/></g></g><g><g><path d="M416,106.667H96c-5.888,0-10.667,4.779-10.667,10.667v320C85.333,478.507,118.827,512,160,512h192    c41.173,0,74.667-33.493,74.667-74.667v-320C426.667,111.445,421.888,106.667,416,106.667z M405.333,437.333    c0,29.397-23.915,53.333-53.333,53.333H160c-29.419,0-53.333-23.936-53.333-53.333V128h298.667V437.333z" fill="#32c79d"/></g></g><g><g><path d="M160,170.667c-5.888,0-10.667,4.779-10.667,10.667v256c0,5.888,4.779,10.667,10.667,10.667s10.667-4.779,10.667-10.667    v-256C170.667,175.445,165.888,170.667,160,170.667z" fill="#32c79d"/></g></g><g><g><path d="M224,170.667c-5.888,0-10.667,4.779-10.667,10.667v256c0,5.888,4.779,10.667,10.667,10.667s10.667-4.779,10.667-10.667    v-256C234.667,175.445,229.888,170.667,224,170.667z" fill="#32c79d"/></g></g><g><g><path d="M288,170.667c-5.888,0-10.667,4.779-10.667,10.667v256c0,5.888,4.779,10.667,10.667,10.667s10.667-4.779,10.667-10.667    v-256C298.667,175.445,293.888,170.667,288,170.667z" fill="#32c79d"/></g></g><g><g><path d="M352,170.667c-5.888,0-10.667,4.779-10.667,10.667v256c0,5.888,4.779,10.667,10.667,10.667    c5.888,0,10.667-4.779,10.667-10.667v-256C362.667,175.445,357.888,170.667,352,170.667z" fill="#32c79d"/></g></g></svg>';
	
	TodoList();
	//user clicked on add button
	function buttonClicked() {
		// console.log('sfdf');
		var value = document.getElementById('task').value;

		//if there is any text in input field add it to todolist;
		if (value) {
			addItem(value);
		}
	}

	document.getElementById('addtask').addEventListener('click', buttonClicked);

	//allow Enter key to add tasks.
	document.getElementById('task').addEventListener('keydown', function(e) {
		// console.log(e);
		var value = this.value;
		if (e.code === 'Enter' || e.code === 'NumpadEnter') {
			buttonClicked();
		}
	});

	function TodoList() {
		if (!data.todo.length) return;
		for (var i = 0; i < data.todo.length; ++i) {
			var value = data.todo[i];
			addtasktodo(value);
		}
	}

	function addItem(value) {
		addtasktodo(value);
		document.getElementById('task').value = '';
		data.todo.push(value);
		dataObjectUpdate();
	}

	function dataObjectUpdate() {
		localStorage.setItem('todoList', JSON.stringify(data));
	}

	//remove task from todolist.
	function removeItem(e) {
		// console.log(this); 		// it is button.
		// console.log(this.parentNode.parentNode);

		var item = this.parentNode.parentNode;
		var parent = item.parentNode;
		var value = item.innerText;
		data.todo.splice(data.todo.indexOf(value), 1);
		dataObjectUpdate();
		parent.removeChild(item);
	}

	// add new task to the todo list
	function addtasktodo(task) {
		// console.log(task);
		var list = document.getElementById('todo');

		var item = document.createElement('li');
		item.innerText = task;

		var buttons = document.createElement('div');
		buttons.classList.add('buttons');

		var remove = document.createElement('button');
		remove.classList.add('remove');
		remove.innerHTML = removeSVG;

		//add click event
		remove.addEventListener('click', removeItem);


		buttons.appendChild(remove);
		buttons.appendChild(accomplished);

		item.appendChild(buttons);

		//list.appendChild(item);		//append in the end.
		list.insertBefore(item, list.childNodes[0]);
 	}
}