$(document).ready(function() {

		$('.tweet .content a').attr("target", "_blank");

		function toggleNav()
		{
			var elm = $("#" + this.innerHTML.replace(" ", "") + "Nav");
			if (elm.css("display") == "none")
			{
				$("ul.nav").hide();
				elm.slideDown(500);
			
			}
			else
			{
				elm.slideUp(500);
			}
		}		
		
		$("h2.nav a").click(toggleNav);
	
	});
	
function doSearch(searchTerm, seachType)
{
		$("#searchField")[0].value = searchTerm;
		if (seachType != '')
		{
			$("#searchTypeField")[0].value = seachType;
		}
		
		$("#mainForm")[0].submit();
	
}

function doMouseOver(elm, nprid, title)
{
	var popupDiv = $('#popup' + nprid);
	//console.debug(popupDiv);
	if (popupDiv.length > 0) 
	{
		popupDiv.show();
		return;
	}

	var popupDiv = document.createElement('div');
	popupDiv.id = 'popup' + nprid;
	popupDiv.className = 'popup';

	popupDiv.innerHTML = '<h4>Top Story for ' + title + '</h4><iframe frameborder="0" scrolling="no" height="250px" id="iframe' + nprid + '" src="http://api.npr.org/query?id=' + nprid + '&numResults=1&output=HTML&fields=summary&apiKey=' + window.apiKey + '></script>';
	
	elm.parentNode.appendChild(popupDiv);
	
	

	
	
}

function doMouseOut(nprid)
{
	var popupDiv = $('#popup' + nprid);
	if (popupDiv.length > 0) 
	{
		popupDiv.hide();
	}
}
