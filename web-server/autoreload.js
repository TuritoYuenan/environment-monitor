setInterval(() => {
	var x = new XMLHttpRequest()
	
	x.onreadystatechange = function () {
		if (this.readyState == 4 && this.status == 200) { document.body.innerHTML = this.responseText }
	}
	
	x.open('GET', '/', true)
	x.send();
}, 1000);
