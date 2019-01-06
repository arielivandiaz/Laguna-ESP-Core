const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <link href="https://stackpath.bootstrapcdn.com/bootstrap/4.2.1/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-GJzZqFGwb1QTTN6wy59ffF1BuGJpLSa9DkKMp0DgiMDm4iYMj70gZWKYbI706tWS" crossorigin="anonymous">
</head>

<body class="text-center">

    <div id="demo">
        <h1>AUTOMATE</h1>
        <div>
            <button type="button" class="btn btn-lg  btn-primary" onclick="sendMate(0)">PREPARAR MATE</button>
        </div>
        <br>
        <div>
            <button type="button" class="btn btn-secondary" onclick="sendData(1)">PAVA ON</button>
            <button type="button" class="btn btn-secondary" onclick="sendData(0)">PAVA OFF</button>
        </div>


        <br>
        <div>
            <button type="button" class="btn btn-success" onclick="sendServo(0)">SOLTAR YERBA</button>
        </div>
        <br>
    </div>

    <div id="chatbox" class="card w-50 mx-auto" style="background: #ffc; , display: none;">
        <div class="card-body ">

            Preparando el Mate, espere...
        </div>

    </div>
    <br>
    <div>
        <h4>LEVEL State : <span id="ADCValue">0</span></h4>
        <h4>PAVA State : <span id="LEDState">NA</span></h4>
        <h4>VALVULA State : <span id="SERVOstate">0</span></h4>
    </div>
    <script>
        function sendData(led) {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("LEDState").innerHTML =
                        this.responseText;
                }
            };
            xhttp.open("GET", "setLED?LEDstate=" + led, true);
            xhttp.send();
        }

        function sendServo(ang) {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("SERVOstate").innerHTML =
                        this.responseText;
                }
            };
            xhttp.open("GET", "setServo?SERVOstate=" + ang, true);
            xhttp.send();
        }

        function sendMate(stat) {
            document.getElementById("chatbox").style.display = "block";
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("SERVOstate").innerHTML =
                        this.responseText;
                }
            };
            xhttp.open("GET", "setMate?MATEstate=" + stat, true);
            xhttp.send();
        }

        setInterval(function() {
            // Call a function repetatively with 2 Second interval
            getData();
        }, 1000); //2000mSeconds update rate

        function getData() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("ADCValue").innerHTML =
                        this.responseText;
                }
            };
            xhttp.open("GET", "readADC", true);
            xhttp.send();
        }
    </script>

</body>
</html>
)=====";
