var mqtt;
var value;

function sendmesg(devicestring, command) {
 
	mqtt.send(devicestring, command);

	//----------------------------Console--------------
	if ($('#ws p').length > 10) {
	$('#ws p').first().remove();
	}
	$('#ws').append('<p class="pf" style="color: #000000 ;">Data dikirim oleh Server :' + devicestring + ' = ' + command);
	$('#ws').scrollTop($("#ws")[0].scrollHeight - $("#ws").height());
	//----------------------------Console--------------
}


$( document ).ready(function() {
  var reconnectTimeout = 2000;
  function MQTTconnect() {
  if (typeof path == "undefined") {
      path = '/mqtt';
  }
  mqtt = new Paho.MQTT.Client(
    host,
    port,
    path,
    "web_" + parseInt(Math.random() * 100, 10)
  );
      var options = {
          timeout: 3,
          useSSL: useTLS,
          cleanSession: cleansession,
          onSuccess: onConnect,
          onFailure: function (message) {
              $('#status').val("Connection failed: " + message.errorMessage + "Retrying");
              setTimeout(MQTTconnect, reconnectTimeout);
          }
      };

      mqtt.onConnectionLost = onConnectionLost;
      mqtt.onMessageArrived = onMessageArrived;

      if (username != null) {
          options.userName = username;
          options.password = password;
      }
      console.log("Host="+ host + ", port=" + port + ", path=" + path + " TLS = " + useTLS + " username=" + username + " password=" + password);
      mqtt.connect(options);
  }

  function onConnect() {
      $('#status').html('Host: ' + host + ':' + port + path);
      mqtt.subscribe(topic, {qos: 0});
	  console.log("onConnect");
  }

  function onConnectionLost(response) {
      setTimeout(MQTTconnect, reconnectTimeout);
      $('#status').val("connection lost: " + responseObject.errorMessage + ". Reconnecting");

  };


  function onMessageArrived(message) {

	var topic = message.destinationName;
	var payload = message.payloadString;
		
	if(topic == "/sensor/suhu")
	{			
		$("#sensor").html(payload);	
		value = payload;
		graph.setData(data(get_date(), value));
	}
	
	if(topic == "/rumah/lampukamar/status")
	{			
		$("#status_lampu").html(payload);	
	}
	 
	 
	//----------------------------Console--------------
	if ($('#ws p').length > 10) {
		$('#ws p').first().remove();
	}
	$('#ws').append('<p class="pf" style="color: green ;"> Data diterima oleh Server : ' + topic + ' = ' + payload);
	$('#ws').scrollTop($("#ws")[0].scrollHeight - $("#ws").height());
	//----------------------------Console--------------
	 
  };


  $(document).ready(function() {
      MQTTconnect();
  });

});
