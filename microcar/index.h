
const char MAIN_page[] PROGMEM = R"=====(
<html>
  <head>
    <title>Microcar</title>
    <script>
	function getRandomInt(max) {
  return Math.floor(Math.random() * Math.floor(max));
	}
    function s(u){var x = new XMLHttpRequest();x.open("GET", u+"?x="+getRandomInt(10000), true);x.send(null);}
    function ret(u){return function(e){
                                s(u);
                                e.returnValue = false;
                                return false;
                            }
                    }
    window.addEventListener('load', function(){
        var lf = document.getElementById('lf');
        var rf = document.getElementById('rf');
        var lb = document.getElementById('lb');
        var rb = document.getElementById('rb');
        lf.addEventListener('touchstart', ret("lon"), false);
        lf.addEventListener('touchend', ret("loff"), false);
        rf.addEventListener('touchstart', ret("ron"), false);
        rf.addEventListener('touchend', ret("roff"), false);
        lb.addEventListener('touchstart', ret("lron"), false);
        lb.addEventListener('touchend', ret("loff"), false);
        rb.addEventListener('touchstart', ret("rron"), false);
        rb.addEventListener('touchend', ret("roff"), false);
     
    }, false);

    </script>
  </head>
  <body>
  <div>
    <button id="lf" style="width:50%;height:50%;float:left;">LF</button>
    <button id="rf" style="width:50%;height:50%;float:left;">RF</button>
    <button id="lb" style="width:50%;height:50%;float:left;">LB</button>
    <button id="rb" style="width:50%;height:50%;float:left;">RB</button>
    </div>
  </body>
</html>
)=====";
