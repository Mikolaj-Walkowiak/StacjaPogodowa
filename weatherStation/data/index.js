window.onload = function() {
	fetchData();
	fetchConfig();
}

function fetchData() {
	var ajaxRequest = new XMLHttpRequest();
	ajaxRequest.open("GET","/data",true);
	ajaxRequest.onreadystatechange = function() {
		if(ajaxRequest.readyState == 4 && ajaxRequest.status==200) {
			var ajaxResult = JSON.parse(ajaxRequest.responseText);
			var time = document.getElementById("time");
			var temp = document.getElementById("temperature");
			var pres = document.getElementById("pressure");
			var hum = document.getElementById("humidity");
			time.innerHTML = ajaxResult.time.hours.toString().padStart(2, '0') + ':' 
				+ ajaxResult.time.minutes.toString().padStart(2, '0') + ':'
				+ ajaxResult.time.seconds.toString().padStart(2, '0');
			temp.innerHTML = parseFloat(ajaxResult.weather.temp-273.15).toFixed(2);
			pres.innerHTML = ajaxResult.weather.pressure;
			hum.innerHTML = ajaxResult.weather.humidity;
		}
	}
	ajaxRequest.send();
}

function fetchConfig() {
	var ajaxRequest = new XMLHttpRequest();
	ajaxRequest.open("GET","/config",true);
	ajaxRequest.onreadystatechange = function() {
		if(ajaxRequest.readyState == 4 && ajaxRequest.status==200) {
			var ajaxResult = JSON.parse(ajaxRequest.responseText);
			var radio = document.getElementById(ajaxResult.weather.internet ? "internet" : "sensor");
			radio.checked = true;
		}
	}
	ajaxRequest.send();
}

function sendConfig() {
	var ajaxRequest = new XMLHttpRequest();
	ajaxRequest.open("POST","/config",true);
	ajaxRequest.onreadystatechange = function() {
		if(ajaxRequest.readyState == 4 && ajaxRequest.status==200) {
			window.location.reload(false); 
		}
	}
	ajaxRequest.send(JSON.stringify({
		weather: {
			internet: document.getElementById("internet").checked
		}
	}));
}