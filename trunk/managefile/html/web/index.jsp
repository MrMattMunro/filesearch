<html>
<head>
<meta http-equiv="content-type" content="text/html;charset=utf-8">
<link rel="Shortcut Icon" href="<%=request.getContextPath()%>/web/img/search.ico">
<link rel="stylesheet" href="<%=request.getContextPath()%>/web/css/demos.css">
<link rel="stylesheet" href="<%=request.getContextPath()%>/web/css/default.css">
<link rel="stylesheet" href="<%=request.getContextPath()%>/web/css/pagination.css">
<link rel="stylesheet" href="<%=request.getContextPath()%>/web/js/jquery/development-bundle/themes/base/jquery.ui.all.css">
<script type="text/javascript" src="<%=request.getContextPath()%>/web/js/jquery/js/jquery-1.6.2.min.js"></script>
<script type="text/javascript" src="<%=request.getContextPath()%>/web/js/common.js"></script>
<script type="text/javascript" src="<%=request.getContextPath()%>/web/js/jquery/plugin/jquery.blockUI.js"></script>
<script type="text/javascript" src="<%=request.getContextPath()%>/web/js/jquery/plugin/jquery.pagination.js"></script>
<script type="text/javascript" src="<%=request.getContextPath()%>/web/js/jquery/js/jquery-ui-1.8.16.custom.min.js"></script>
<style>
#feedback { font-size: 1.4em; }
#selectable .ui-selecting { background: #FECA40; }
#selectable .ui-selected { background: #F39814; color: white; }
#selectable { list-style-type: none; margin: 0; padding: 0; width: 60%; }
#selectable li { margin: 3px; padding: 0.4em; font-size: 1.4em; height: 18px; }
</style>
<script type="text/javascript">

        var id;
        var searchtype;
        //UI Data
        var uiData;
        var searchersLength;
        var recentTypeIndex;
        var recentTypeArr = new Array();
        var total_row;
        var currentpage;
        
	    function pageselectCallback(page_index, jq){
	    	  currentpage = page_index + 1;
              // Get number of elements per pagionation page from form
              // var max_elem = Math.min((page_index + 1) * 10, total_row);
              // show result
              search(id, searchtype, recentTypeIndex, currentpage);
              // Prevent click event propagation
              return false;
         }
             
        
        function openWin(path, attach){
			$.ajax({
				type: "POST",
				url: "open",
				data: {"path": path,"attach": attach},
				timeout : 15000 ,
				dataType : 'json',//	
				beforeSend: function(XMLHttpRequest){
				},
				success: function(data, textStatus){
				},
				complete: function(XMLHttpRequest, textStatus){
			       //$.unblockUI();
				},
				error: function(){	
				}
	       });
		};
		
		function showErrorMsg(msg, width, height){
			$("#msg_icon").show();
		    $("#warning").empty();
		    $("#warning").append(msg); 
		    $( "#dialog:ui-dialog" ).dialog( "destroy" );
			$( "#dialog-message" ).dialog({
			    height:height,
			    width:width,
				modal: true,
				buttons: {
					Ok: function() {
						$( this ).dialog( "close" );
					}
				}
			});
		};
		
		function showWarnMsg(msg, width, height){
		    $("#questioncontent").empty();
		    $("#questioncontent").append(msg); 
		    // Dialog			
			$('#question').dialog({
				autoOpen: false,
				width: 600,
				buttons: {
					"Ok": function() { 
						$(this).dialog("close"); 
					}, 
					"Cancel": function() { 
						$(this).dialog("close"); 
					} 
				}
			});
 
		};
		
		function showRecentType(){
 
		};
		
		function hiddleAllPage(){
	          var allType = "ALL,WORD,EXCEL,PPT,PDF,HTML,TXT"; 
			  var allfiletypesArr = new Array();
			  allfiletypesArr = allType.split(",");
			  
			  for(var i=0; i < allfiletypesArr.length;i++){
				  var filetype = allfiletypesArr[i];
				  $("#Pagination_" + filetype ).html("");
			  }
		}
		
		 // Load UI Data
		function loadUIData(){
			   $.ajax({
					type: "GET",
					url: "loadUIData",
					timeout : 15000 ,
					dataType : 'json',//	
					beforeSend: function(XMLHttpRequest){
					},
					success: function(data, textStatus){
						$("#select-result").html(data.searchPath);
						$("#loading").append(data.loadmsg); 
						// show no Search msg
						if("" != data.error_nosearcher){
							showErrorMsg(data.error_nosearcher, 300, 160);
						}
						uiData = data;
					    // create recentType
					    var recentType = "";
					    if(undefined != data.recentType){
						  recentType = data.recentType;
					    }
			            recentTypeArr = recentType.split(",");
					},
					complete: function(XMLHttpRequest, textStatus){
					},
					error: function(){	
					}
		       });
		};
		
		function loadSearch(index){
			$.ajax({
					type: "GET",
					url: "loadSearch",
					data: {"index": index},
					timeout : 15000 ,
					dataType : 'json',//	
					beforeSend: function(XMLHttpRequest){
					},
					success: function(data, textStatus){
					      id = data[0].id;
						  // create tabs by filetype
						  var allType = "WORD,EXCEL,PPT,PDF,HTML,TXT"; 
						  var allfiletypesArr = new Array();
						  allfiletypesArr = allType.split(",");
						  
						  var selectfiletype = "" + data[0].selectfiletype;
						  selectfiletype = selectfiletype.toUpperCase();
						  
						  for(var i=0; i < allfiletypesArr.length;i++){
							  var filetype = allfiletypesArr[i];
							  // defined not exist filetype
							  if(selectfiletype.indexOf(filetype) == -1){
								 $("#tab_ul_li_" + filetype).hide();
							  }else{
								 $("#tab_ul_li_" + filetype).show();
							  }
						  }
						  // if select the recent change
						  if(id == "-1"){
							 //
						  }
					},
					complete: function(XMLHttpRequest, textStatus){
					},
					error: function(){	
					}
		    });
		};
		
	   function loadSearchList(){
			// load Searher List
			$.ajax({
					type: "GET",
					url: "loadSearchList",
					timeout : 15000 ,
					dataType : 'json',//	
					beforeSend: function(XMLHttpRequest){
					},
					success: function(data, textStatus){
						  $( "#selectable" ).empty();
						  $( "#recenttype" ).empty();
						  // create searchers
						  searchersLength = data.length;
					      for(var i=0; i < data.length;i++){
	                         $("#selectable").append("<li class=\"ui-widget-content\">" + data[i].path + "</li>");
						  }
				         
					      for(var i=0; i < recentTypeArr.length; i++){
                            $("#selectable").append("<li id='"+ recentTypeArr[i] + "' class=\"ui-widget-content\">" + recentTypeArr[i] + "</li>");
                          }
					      
						  // create tabs by filetype
						  var allType = "WORD,EXCEL,PPT,PDF,HTML,TXT"; 
						  var allfiletypesArr = new Array();
						  allfiletypesArr = allType.split(",");
						  
						  var selectfiletype = "" + data[0].selectfiletype;
						  selectfiletype = selectfiletype.toUpperCase();
						  
						  for(var i=0; i < allfiletypesArr.length;i++){
							  var filetype = allfiletypesArr[i];
							  // defined not exist filetype
							  if(selectfiletype.indexOf(filetype) == -1){
								 $("#tab_ul_li_" + filetype).hide();
							  }else{
								 $("#tab_ul_li_" + filetype).show();
							  }
						  }
					},
					complete: function(XMLHttpRequest, textStatus){
					},
					error: function(){	
					}
		   });
		};
		
	    function search(id, searchtype, recentTypeIndex, currentpage){
            var keyword = $("#search").val();
            
			$.ajax({
					type: "POST",
					url: "search",
					data: {"query": keyword,"id": id, "searchtype": searchtype, "recentTypeIndex": recentTypeIndex, "currentpage":currentpage},
					timeout : 15000 ,
					dataType : 'json',//
					contentType: "application/x-www-form-urlencoded; charset=utf-8",
					beforeSend: function(XMLHttpRequest){
					},
					success: function(data, textStatus){
						
					  if(searchtype == undefined){
					     searchtype = "ALL";
					  }
					  // if not set, set default value
					  if(recentTypeIndex == undefined){
					     recentTypeIndex = "3";
					  }
					  var tabId = "tabs-" + searchtype.toUpperCase();
					  $("#" + tabId).html("");
					  
					  // check too much records
			  		  if(data.length > 150){
			  			  var isconfirm = showWarnMsg(formatMsg(uiData.error_muchrecords, data.length), 300, 230);
						  //if(!isconfirm){
							//return;  
						  //}
					  }
					  // when row > 0 
					  total_row = 0;
					  if(data.length > 0){
						 total_row =data[0].totalRow;
					  }
					  for(var i=0; i < data.length;i++){
						  var dataRow = data[i];
						  var path = dataRow.path;
						  path = replaceAll(path, "\\", ",");
						  path = replaceAll(path, ",", "\\\\");
						  var html = "<table class=\"result\" id=\"4\" cellSpacing=\"0\" cellPadding=\"0\">" + 
						             "<TBODY><TR><TD class=f><H3 class=t>" + 
						             "<A class= \"result_a\" target=\"_self\" href=\"javascript:openWin('"+ path + "','" + dataRow.attachStr + "');\">" +
						             dataRow.filename + "&nbsp;" + dataRow.attachStr + "</A><BR>" + 
						             "<SPAN class=\"result_content\">" + dataRow.content+ "</SPAN>" + 
						             "<SPAN class=\"result_path\">"+ dataRow.path + "</SPAN>&nbsp;&nbsp;" +
						             "<SPAN class=\"result_time\">"+ dataRow.lastmodify + "</SPAN>" +
						             "<BR></FONT></TD></TR></TBODY><table><BR>"
						  var tempTable = $("#" + tabId).append(html);
					  }
				  
					  var temp = searchtype.toUpperCase();
					  if(total_row == 0){
					 	 data = null;
					 	 return;
					  }
				      // add page search pane
				      var page = total_row / 10;
			          var allType = "ALL,WORD,EXCEL,PPT,PDF,HTML,TXT"; 
					  var allfiletypesArr = new Array();
					  allfiletypesArr = allType.split(",");
					  
					  for(var i=0; i < allfiletypesArr.length;i++){
						  var filetype = allfiletypesArr[i];
						  // defined not exist filetype
						  if(filetype == temp){
							  if(currentpage == 1 || currentpage == undefined ){
								  $("#Pagination_" + filetype ).show();
								  // show page pagination
								  $("#Pagination_" + filetype ).pagination(total_row, {
					                    callback: pageselectCallback,
					                    items_per_page:10 // Show only one item per page
				                  });
							  }
						  }else{
							  $("#Pagination_" + filetype ).hide();
						  }
					 }
					  
					 // when first search
					 if(currentpage  == 1 && total_row != undefined && total_row > 0){
						showResultInfo(total_row); 
					 }
					 data = null;
				},
				complete: function(XMLHttpRequest, textStatus){
			       //$.unblockUI();
				},
				error: function(){	
				}
	       });
		};
		
		
        function callback(){
	         setTimeout(function(){
			       $("#resultinfo:visible").removeAttr("style").fadeOut();
			 }, 3000 );
		};
		function showResultInfo(dataLength){
			  $("#resultinfo_p").empty();
			  dataLength = "<b>" + dataLength + "</b>";
			  $("#resultinfo_p").html(formatMsg(uiData.resultInfo, dataLength));
			  $("#resultinfo").show("blind",{}, 500, callback);
		}
		
        // JQuery Start
		$(function() {
				loadUIData();
		        $("#resultinfo").hide();
			    // Set all ajax req needs block
			    $(document).ajaxStart($.blockUI).ajaxStop($.unblockUI);
			    
				$( "input:submit, a, button", ".demo" ).button();
				$(document).find("li >a >SPAN").click(
					function(event) {
					    // Click tab event
					    searchtype = event.srcElement.innerHTML;
					    var keyword = $("#search").val();
					    search(id, searchtype, recentTypeIndex, 1);
					}
				);
				
				// move over change the page link
				$(document).find("li >a >SPAN").mouseover(
					function(event) {
					    // Click tab event
					    var searchtype = event.srcElement.innerHTML;
					    searchtype = searchtype.toUpperCase();
					    var allType = "ALL,WORD,EXCEL,PPT,PDF,HTML,TXT"; 
					    var allfiletypesArr = new Array();
					    allfiletypesArr = allType.split(",");
						for(var i=0; i < allfiletypesArr.length;i++){
							  var filetype = allfiletypesArr[i];
							  // defined not exist filetype
							  if(filetype == searchtype){
							      $("#Pagination_" + filetype ).show();
							  }else{
								  $("#Pagination_" + filetype ).hide();
							  }
						 }
					}
				);
				
				// Select Search Path
				$( "#selectable" ).selectable({
					stop: function() {
						$( ".ui-selected", this ).each(function() {
							hiddleAllPage();
							total_row = 0;
							// clear pre result
							if(searchtype == undefined){
					           searchtype = "ALL";
					        }
							var tabId = "tabs-" + searchtype.toUpperCase();
					        $("#" + tabId).empty();
					  
							var index = $( "#selectable li" ).index( this );
					        
					        // set the recentType show or hide
					        if(index + 1 >= searchersLength){
							  for(var i=0; i < recentTypeArr.length; i++){
					            $("#" + recentTypeArr[i]).show();
		                      }
							}else{
				                for(var i=0; i < recentTypeArr.length; i++){
						            $("#" + recentTypeArr[i]).hide();
			                    }
							}
					        // select the recent Type
							if(index >= searchersLength){
				                 recentTypeIndex = index - searchersLength;
				                 search("-1", searchtype, recentTypeIndex);
							} else {
								 // clear all the result
								  var allType = "ALL,WORD,EXCEL,PPT,PDF,HTML,TXT"; 
								  var allfiletypesArr = new Array();
								  allfiletypesArr = allType.split(",");
				                  for(var i=0; i < allfiletypesArr.length; i++){
				                	  var tabId = "tabs-" + allfiletypesArr[i];
					                  $("#" + tabId).html("");
		                          }
								  // load Search
	                              loadSearch(index);
							}
					    });
					}
				});
				
				
			  $( "#tabs" ).tabs({
					event: "mouseover",
					ajaxOptions: {
						error: function( xhr, status, index, anchor ) {
							$( anchor.hash ).html("Couldn't load this tab. We'll try to fix this as soon as possible. " );
						},		
						success: function(data, textStatus){
					    }
					}
			   });
			  
				// bind input onChange Event
				$("#search").change(
					 function() {
	                    search(id, searchtype, recentTypeIndex);
					 }
				);
				
				// load Searcher List
		        loadSearchList();
			}
		);
	
	 function initMenu(){
		$(".menuChild").eq(0).show('normal');
		$(".menu").click(
			function(){
				var $menuChild = $(this).next();
				if($menuChild.is('div') && $menuChild.is(':visible')){
					$menuChild.hide('normal');
					return false;
				}
				if($menuChild.is('div') && (!$menuChild.is(':visible'))){
					$('.menuChild:visible').hide('normal');
					$menuChild.show('normal');
					return false;
				}
			}
		);
		$(".split_button").click(
			function(){
				var $left = $(".left");
				
				if($left.is('div') && $left.is(':visible')){
					$left.hide('normal');
					$(".split_button").css("background", "url(/img/split_open.gif) no-repeat center");
					return false;
				}
				if($left.is('div') && (!$left.is(':visible'))){
					$('.left:visible').hide('normal');
					$left.height($(window).height()-110);
					$left.show('normal');
					$(".split_button").css("background", "url(/img/split_close.gif) no-repeat center");
					return false;
				}
			});
	}
		
	function initContentSize(){
		$(".content").height($(window).height()-110);
	}
	$(function(){
		initContentSize();		
		initMenu();
		$("#search").focus();
	});
</script>
<title></title>
</head>
<body>
<div id="dialog-message" title="Warning">
	<p id="warning">
		<span style="display:none" id="msg_icon" class="ui-icon ui-icon-circle-check" style="float:left; margin:0 7px 50px 0;"></span>
	</p>
</div>

<div id="loading_div" class="growlUI" style="display:none">
	<p id="loading">
	</p>
</div>

<div id="question" style="display:none; cursor: default"> 
        <span id="questioncontent"></span> 
        <input type="button" id="yes" value="Yes" /> 
        <input type="button" id="no" value="No" /> 
</div> 


<div class="mainBody">
   <div class="header">
	     <div class="demo">
				<input class="inputsearch" id="search" />
	     </div>
   </div>
   <div class="content">
   		<div class="left">
				<div class="demo">
					<p id="feedback">
				         <span id="select-result"></span>
					</p>
					<ol id="selectable">
					</ol>
				</div>
        </div>
       	<div class="split">
           	<div class="split_button"></div>
        </div>
        <div class="main">
            <div class="mianRight">
					<div class="demo">
						<div id="tabs">
								<ul id="tab_ul">
									<li id="tab_ALL"><a href="#tabs-ALL">ALL</a></li>
									<li id="tab_ul_li_WORD"><a href="#tabs-WORD">Word</a></li>
									<li id="tab_ul_li_EXCEL"><a href="#tabs-EXCEL">Excel</a></li>
									<li id="tab_ul_li_PPT"><a href="#tabs-PPT">Ppt</a></li>
									<li id="tab_ul_li_PDF"><a href="#tabs-PDF">Pdf</a></li>
									<li id="tab_ul_li_HTML"><a href="#tabs-HTML">Html</a></li>
									<li id="tab_ul_li_TXT"><a href="#tabs-TXT">Txt</a></li>
								</ul>
								<div id="resultinfo" class="ui-widget-content ui-corner-all">
								    <h5 class="ui-widget-header ui-corner-all">&nbsp;</h5>
								    <p style="text-align:center" id="resultinfo_p"></p>
								</div>
								<div id="tabs-ALL">
									<p></p>
								</div>
								<div id="tabs-WORD">
									<p></p>
								</div>
								<div id="tabs-EXCEL">
									<p></p>
								</div>
								<div id="tabs-PPT">
									<p></p>
								</div>
								<div id="tabs-PDF">
									<p></p>
								</div>
								<div id="tabs-HTML">
									<p></p>
								</div>
								<div id="tabs-TXT">
									<p></p>
								</div>
						</div>
					</div>
				    <div id="Pagination_ALL"></div>
				    <div id="Pagination_WORD"></div>
				    <div id="Pagination_EXCEL"></div>
				    <div id="Pagination_PPT"></div>
				    <div id="Pagination_HTML"></div>
				    <div id="Pagination_TXT"></div>
            </div>
        </div>
   </div>
   <div class="footer">
		   Copyright © 2011 SLfile Inc. All rights reserved.
   </div>
</div>
</body>
</html>
