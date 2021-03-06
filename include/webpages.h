String pageheader =R"(
    <!DOCTYPE html>
        <html>
            <head>
    <style type="text/css">
               .form-style{
            font-family: arial, sans;
            width: 900px;
            padding: 30px;
            background: #FFFFFF;
            margin: 50px auto;
            box-shadow: 0px 0px 15px rgba(0, 0, 0, 0.22);
            -moz-box-shadow: 0px 0px 15px rgba(0, 0, 0, 0.22);
            -webkit-box-shadow:  0px 0px 15px rgba(0, 0, 0, 0.22);
        }
        .form-style h1{
            font-size: 2.5em;
            font-weight: bold;
            padding: 20px;
            margin: -30px -30px 30px -30px;
        }
         .form-style h2{
            background: #4D4D4D;
            text-transform: uppercase;
            font-family: 'Open Sans Condensed', sans-serif;
            color: #BBBBBB;
            font-size: 1.8em;
            font-weight: 100;
            padding: 20px;
            margin: -30px -30px 30px -30px;
        }
        .form-style input,
        .form-style textarea,
        .form-style select 
        {
            box-sizing: border-box;
            -webkit-box-sizing: border-box;
            -moz-box-sizing: border-box;
            outline: none;
            display: block;
            width: 100%;
            padding: 7px;
            border: none;
            border-bottom: 1px solid #ddd;
            background: transparent;
            margin-bottom: 10px;
            font: 1.4em Arial, Helvetica, sans-serif;
            height: 45px;
        }
        .form-style textarea{
            resize:none;
            overflow: hidden;
        }
        .form-style input[type="button"], 
        .form-style input[type="submit"]{
             -moz-box-shadow: inset 0px 1px 0px 0px #45D6D6;
            -webkit-box-shadow: inset 0px 1px 0px 0px #45D6D6;
            box-shadow: inset 0px 1px 0px 0px #45D6D6;
            background-color: hsl(175, 60%, 53%);
            border: 1px solid hsl(180, 60%, 53%);
            display: inline-block;
            height: 69px;
            cursor: pointer;
            color: #FFFFFF;
            font-family: 'Open Sans Condensed', sans-serif;
            font-size: 2em;
			margin-top:20px;
			margin-bottom:20px;
            padding: 8px 18px;
            text-decoration: none;
            text-transform: uppercase;
        }
        .form-style fieldset{
            border: none;
        }
        .form-style .inner-wrap{
            padding: 30px;
            background: #FBFBFB;
            border-radius: 12px;
            margin-bottom: 15px;
        }
        .form-style legend {
	        font-size: 1.5em;
	        margin-bottom: 10px;
        }
       .form-style label {
	        font-size: 1.4em;
	        margin-bottom: 10px;
        }
        .form-style .number {
            background: hsl(175, 60%, 53%);
            color: #fff;
            height: 30px;
            width: 30px;
            display: inline-block;
            font-size: 1.2em;
            margin-right: 4px;
            line-height: 30px;
            text-align: center;
            text-shadow: 0 1px 0 rgba(255,255,255,0.2);
            border-radius: 15px 15px 15px 0px;
        }

        .form-style input[type="button"]:hover, 
        .form-style input[type="submit"]:hover {
            background:linear-gradient(to bottom, #34CACA 5%, #30C9C9 100%);
            background-color:#34CACA;
        }
		 .button0 {
            background: hsl(175deg 10% 32%);
            border-radius: 12px;
			margin:15px 15px 15px 15px;
            border: none;
            padding: 0;
            cursor: pointer;
            outline-offset: 4px;
        }
             .button1 {
            background: hsl(175deg 100% 32%);
            border-radius: 12px;
			margin:15px 15px 15px 15px;
            border: none;
            padding: 0;
            cursor: pointer;
            outline-offset: 4px;
        }
        .buttonemergency {
            background: hsl(55deg 100% 32%);
            border-radius: 75px;
            border: none;
            padding: 0;
            cursor: pointer;
            outline-offset: 4px;
        }
      .front0 {
            display: block;
            padding: 10px 75px;
            border-radius: 12px;
			height:55px;
			font-size: 2rem;
            background: hsl(180deg 10% 47%);
            color: white;
            transform: translateY(-6px);
        }
       .front1 {
            display: block;
            padding: 10px 75px;
            border-radius: 12px;
			height:55px;
			font-size: 2rem;
           background: hsl(180deg 100% 47%);
            color: white;
            transform: translateY(-6px);
        }
        .frontemergency {
            display: block;
            padding: 60px 60px;
            border-radius: 80px;
            font-size: 1.25rem;
            background: hsl(340 100% 50%);
            color: white;
            transform: translateY(-6px);
            border:8px solid yellow}
        .button0:active .front0 {
            transform: translateY(-2px);
        }
        .button1:active .front1 {
            transform: translateY(-2px);
        }
        .buttonemergency:active .frontemergency {
            transform: translateY(-2px);
        }
        </style>
   </head>    
  <body>
 )" + message;
 
 
 String mainmenu(){
    String mainpage =pageheader + "<div class=\"form-style\"><h1>"+ sHeading1+ "</h1>\n"
    +"<h2>"+ sMainmenu + "</h2>\n"
    +"<a href=\"/settings\"><input type=\"button\" value=\""+ sSettings + "\"></a>\n"
    +"<a href=\"/manual1\"><input type=\"button\" value=\""+ sManuop + "\"></a>\n"
   +"<a href=\"/scalecalib\"><input type=\"button\" value=\""+sScalecalibration +"\"></a>\n"
    // +"<a href=\"/testscale\"><input type=\"button\" value=\""+Testscale +"\"></a>\n"
     +"<br><br><br><br><h2> </h2>\n<div></body></html>";
   return mainpage;
 }

 
 String settingform(){
    String mainpage =pageheader + "<div class=\"form-style\"><h1>"+ sHeading1+ "</h1>\n"
    +"<h2>"+ sConfiguration + "</h2>\n"
    +"<form action=\"/get\">\n"
    +"<legend><span class=\"number\">1</span>" + sSettings + "</legend><div class=\"inner-wrap\">\n"
    +"<label>"+ sLanguage +"<select id=\"language\" name=\"language\" onchange=\"this.form.submit();\" ><option " + sDeselected + " value=\"1\">Deutsch</option><option " + sEnselected + " value=\"0\">English</option></select></label>\n"
    +"</div><legend><span class=\"number\">2</span>" + sFillprocess + "</legend><div class=\"inner-wrap\">\n"
    +"<label>"+ sWaitforfillbottle +"<input type=\"text\"  id=\"waitforfillbottle\" name=\"waitforfillbottle\" value=\"" + String(waitforfillbottle) + "\"></label>\n"
    +"<label>"+ sPurgecycles +"<input type=\"text\"  id=\"purgecycles\" name=\"purgecycles\" value=\"" + String(purgecycles) + "\"></label>\n"
    +"<label>"+ sPurgein +"<input type=\"text\" id=\"purgein\" name=\"purgein\" value=\"" + String(purgein) + "\"></label>\n"
    +"<label>"+ sPurgeinpostdelay +"<input type=\"text\" id=\"purgeinpostdelay\" name=\"purgeinpostdelay\" value=\"" + String(purgeinpostdelay) + "\"></label>\n"
    +"<label>"+ sPurgeout +"<input type=\"text\" id=\"purgeout\" name=\"purgeout\" value=\"" + String(purgeout) + "\"></label>\n"
    +"<label>"+ sPurgeoutpostdelay +"<input type=\"text\" id=\"purgeoutpostdelay\" name=\"purgeoutpostdelay\" value=\"" + String(purgeoutpostdelay) + "\"></label>\n"
     +"<label>"+ sScaletolerance +"<input type=\"text\" id=\"scaletolerance\" name=\"scaletolerance\" value=\"" + String(scaletolerance) + "\"></label>\n"
   +"</div><legend><span class=\"number\">3</span>"+sBottles+"</legend><div class=\"inner-wrap\">\n"
    +"<label>"+ sBottletolerance +"<input type=\"text\" id=\"bottletolerance\" name=\"bottletolerance\" value=\"" + String(bottletolerance) + "\"></label>\n"
    +"<label>"+ sBottle1vol +"<input type=\"text\" id=\"bottle1vol\" name=\"bottle1vol\" value=\"" + String(bottle[0][0]) + "\"></label>\n"
    +"<label>"+ sBottle1weight +"<input type=\"text\" id=\"bottle1weight\" name=\"bottle1weight\" value=\"" + String(bottle[0][1]) + "\"></label>\n"
    +"<label>"+ sBottle2vol +"<input type=\"text\" id=\"bottle2vol\" name=\"bottle2vol\" value=\"" + String(bottle[1][0]) + "\"></label>\n"
    +"<label>"+ sBottle2weight +"<input type=\"text\" id=\"bottle2weight\" name=\"bottle2weight\" value=\"" + String(bottle[1][1]) + "\"></label>\n"
    +"<label>"+ sBottle3vol +"<input type=\"text\" id=\"bottle3vol\" name=\"bottle3vol\" value=\"" + String(bottle[2][0]) + "\"></label>\n"
    +"<label>"+ sBottle3weight +"<input type=\"text\" id=\"bottle3weight\" name=\"bottle3weight\" value=\"" + String(bottle[2][1]) + "\"></label>\n"
    +"</div><legend><span class=\"number\">4</span>"+sCalibration+"</legend><div class=\"inner-wrap\">\n"
    +"<label>"+ sWaitforcalibrationbottle +"<input type=\"text\" id=\"waitforcalibrationbottle\" name=\"waitforcalibrationbottle\" value=\"" + String(waitforcalibrationbottle) + "\"></label>\n"
    +"</div><legend><span class=\"number\">4</span>"+sCIPprocess+"</legend><div class=\"inner-wrap\">\n"
    +"<label>"+ sWaitforcipbottle +"<input type=\"text\" id=\"waitforcipbottle\" name=\"waitforcipbottle\" value=\"" + String(waitforcipbottle) + "\"></label>\n"
    +"<label>"+ sCleancycles +"<input type=\"text\" id=\"cleancycles\" name=\"cleancycles\" value=\"" + String(cleancycles) + "\"></label>\n"
    +"<label>"+ sCleanpurgeout +"<input type=\"text\" id=\"cleanpurgeout\" name=\"cleanpurgeout\" value=\"" + String(cleanpurgeout) + "\"></label>\n"
    +"<label>"+ sCleanschmockeout +"<input type=\"text\" id=\"cleanschmockeout\" name=\"cleanschmockeout\" value=\"" + String(cleanschmockeout) + "\"></label>\n"
    +"</div><input type=\"submit\" value=\"" + sSave + "\" onclick=\"submitMessage()\"><br><br><br>"
    +"</form><h2></h2></div></body></html>";
   return mainpage;
 }
 
 String scalecalibform(){
    String mainpage =pageheader + "<div class=\"form-style\"><h1>"+ sHeading1+ "</h1>\n"
    +"<h2>"+ sCalibration + "</h2>\n"
    +"<form action=\"/setscale\">\n"
    +"<legend><span class=\"number\">1</span>" + sScalecalibration  + "</legend><div class=\"inner-wrap\">\n"
    +"<label>"+ sInstructions + "</label><br>"
    +"<label>" + sReferenceweight + "</label><input type=\"text\"  id=\"referenceweight\" name=\"referenceweight\" placeholder=\"0\"></label>\n"
    +"</div><input type=\"submit\" value=\"" + sSave + "\" onclick=\"submitMessage()\">"
    +"</form>"
    +"<legend><span class=\"number\">2</span>"+ sBottles + "</legend><div class=\"inner-wrap\">\n"
    +"<label>" + sBottleinstructions + "</label>"
    +"<table>"
     +"<tr><td width=\"40%\"><label>"+ sBottle1weight +"</label></td><td width=\"27%\"><input type=\"text\" id=\"bottle1weight\" name=\"bottle1weight\" value=\"" + String(bottle[0][1]) + "\" readonly ></td>\n"
    +"<td><a href=\"/bottle1weight\"><input type=\"submit\" value=\"" + sSubmit + "\"></a></td></tr>\n"
    +"<tr><td><label>"+ sBottle1vol +"</label></td><td><input type=\"text\" id=\"bottle1vol\" name=\"bottle1vol\" value=\"" + String(bottle[0][0]) + "\" readonly ></td>\n"
    +"<td><a href=\"/bottle1vol\"><input type=\"submit\" value=\"" + sSubmit + "\"></a></td></tr>\n"
    +"<tr><td><label>"+ sBottle2weight +"</label></td><td><input type=\"text\" id=\"bottle2weight\" name=\"bottle2weight\" value=\"" + String(bottle[1][1]) + "\" readonly ></td>\n"
    +"<td><a href=\"/bottle2weight\"><input type=\"submit\" value=\"" + sSubmit + "\"></a></td></tr>\n"
    +"<tr><td><label>"+ sBottle2vol +"</label></td><td><input type=\"text\" id=\"bottle2vol\" name=\"bottle2vol\" value=\"" + String(bottle[1][0]) + "\" readonly ></td>\n"
    +"<td><a href=\"/bottle2vol\"><input type=\"submit\" value=\"" + sSubmit + "\"></a></td></tr>\n"
    +"<tr><td><label>"+ sBottle3weight +"</label></td><td><input type=\"text\" id=\"bottle3weight\" name=\"bottle3weight\" value=\"" + String(bottle[2][1]) + "\" readonly ></td>\n"
    +"<td><a href=\"/bottle3weight\"><input type=\"submit\" value=\"" + sSubmit + "\"></a></td></tr>\n"
    +"<tr><td><label>"+ sBottle3vol +"</label></td><td><input type=\"text\" id=\"bottle3vol\" name=\"bottle3vol\" value=\"" + String(bottle[2][0]) + "\" readonly ></td>\n"
    +"<td><a href=\"/bottle3vol\"><input type=\"submit\" value=\"" + sSubmit + "\"></a></td></tr>\n"
    +"</table></div> \n"
    +"<br><a href=\"/\"><input type=\"button\" value=\""+ sMainmenu + "\"></a><br><br><br>\n"
    +"</div></body></html>";
   return mainpage;
 }

 String manuop(){
    String mainpage =pageheader + "<div class=\"form-style\"><h1>"+ sHeading1+ "</h1>\n"
    +"<h2>"+ sManuop + "</h2>\n"
    +"<a href=\"/manuop1"+String(abs(valvestat1-1))+"\"><button class=\"button"+String(valvestat1)+"\"><span class=\"front"+String(valvestat1)+"\">V1</span></button></a>\n"
    +"<a href=\"/manuop2"+String(abs(valvestat2-1))+"\"><button class=\"button"+String(valvestat2)+"\"><span class=\"front"+String(valvestat2)+"\">V2</span></button></a>\n"
    +"<a href=\"/manuop3"+String(abs(valvestat3-1))+"\"><button class=\"button"+String(valvestat3)+"\"><span class=\"front"+String(valvestat3)+"\">V3</span></button></a>\n"
    +"<a href=\"/manuop4"+String(abs(valvestat4-1))+"\"><button class=\"button"+String(valvestat4)+"\"><span class=\"front"+String(valvestat4)+"\">V4</span></button></a>\n"
    +"<br><br><br><a href=\"/emergency\"><button class=\"buttonemergency\"><span class=\"frontemergency\"></span></button></a>"+sEmergencystop+"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n"
    +"<a href=\"/manual"+String(abs(webmode/2-1))+"\"><button class=\"button"+String(webmode/2)+"\"><span class=\"front"+String(webmode/2)+"\"><label>"+sManual+"</label></span></button></a>\n"
     +"<br><br><br><a href=\"/\"><input type=\"button\" value=\""+ sMainmenu + "\"></a>\n"
    +"<br><br><br><h2> </h2></div></body></html>";
   return mainpage;
 }

 String emergencyform(){
    String mainpage =pageheader + "<div class=\"form-style\"><h1>"+ sHeading1+ "</h1>\n"
    +"<h2>"+ sManuop + "</h2>\n"
    +"<form action=\"/reset\">\n"
       +"<button class=\"button"+String(valvestat1)+"0\"><span class=\"front"+String(valvestat1)+"\">V1</span></button>\n"
    +"<button class=\"button"+String(valvestat2)+"0\"><span class=\"front"+String(valvestat2)+"\">V2</span></button>\n"
    +"<button class=\"button"+String(valvestat3)+"0\"><span class=\"front"+String(valvestat3)+"\">V3</span></button>\n"
    +"<button class=\"button"+String(valvestat4)+"0\"><span class=\"front"+String(valvestat4)+"\">V4</span></button>\n"
    +"<br><br><br><input type=\"submit\" value=\"Reset\" onclick=\"submitMessage()\"><br><br><br>"
    +"</form><h2> </h2></div></body></html>";
   return mainpage;
 }

