<?php
/*
 * Created on Jul 27, 2008 by Jason Grosman
 * This work is licensed under the Creative Commons Attribution-Noncommercial 3.0 Unported License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/3.0/ or send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
 *
 */
 
	function printNPRPrograms()
	{
		global $apiKey;
		
		$programsFeed = "http://api.npr.org/list?id=3004&apiKey=$apiKey";
		$allPrograms = curl_simplexml_load_file($programsFeed);
		print '<div class="nav"><h2 class="nav"><a href="" onclick="return false;">Programs</a><span class="arrow">&gt;</span></h2>';
	
		if (!array_key_exists('searchType', $_GET) || $_GET['searchType'] == 'Programs')
		{
			print '<ul class="nav" id="ProgramsNav">';
		}
		else
		{
			print '<ul class="nav" id="ProgramsNav" style="display:none;">';
		}	
			
		foreach ($allPrograms->item as $prg)
		{
			$title = str_replace('\'', '\\\'', $prg->title);
			print '<li><a href="" onclick="doSearch(\'' . $title  . '\', \'Programs\');return false;" onmouseover="doMouseOver(this, \'' . $prg['id'] . '\', \'' . $title . '\');" onmouseout="doMouseOut(\'' . $prg['id'] . '\');" >' . $prg->title . '</a></li>';
		}		
		print '</ul></div>';	
	}
	
	function printNPRTopics()
	{
		global $apiKey;
		
		$topicsFeed = "http://api.npr.org/list?id=3218&apiKey=$apiKey";
		$allTopics = curl_simplexml_load_file($topicsFeed);

		print '<div class="nav"><h2 class="nav"><a href="" onclick="return false;">NPR Topics</a><span class="arrow">&gt;</span></h2>';

		if (array_key_exists('searchType', $_GET) && $_GET['searchType'] == 'NPR Topics')
		{
			print '<ul class="nav" id="NPRTopicsNav">';
		}
		else
		{
			print '<ul class="nav" id="NPRTopicsNav" style="display:none;">';
		}	
		foreach ($allTopics->subcategory[0]->item as $topic)
		{
			$title = str_replace('\'', '\\\'', $topic->title);
			print '<li><a href="" onclick="doSearch(\'NPR ' . $title . '\', \'NPR Topics\');return false;" onmouseover="doMouseOver(this, \'' . $topic['id'] . '\', \'' . $title . '\');" onmouseout="doMouseOut(\'' . $topic['id'] . '\');">' . $topic->title . '</a></li>';
		}
		print '</ul></div>';
		
		print '<h2 class="nav"><a href="" onclick="return false;">NPR Music</a><span class="arrow">&gt;</span></h2>';


		if (array_key_exists('searchType', $_GET) && $_GET['searchType'] == 'NPR Music')
		{
			print '<ul class="nav" id="NPRMusicNav">';
		}
		else
		{
			print '<ul class="nav" id="NPRMusicNav" style="display:none;">';
		}	
		foreach ($allTopics->subcategory[1]->item as $topic)
		{
			$title = str_replace('\'', '\\\'', $topic->title);
			print '<li><a href="" onclick="doSearch(\'NPR Music ' . $title . '\', \'NPR Music\');return false;" onmouseover="doMouseOver(this, \'' . $topic['id'] . '\', \'' . $title . '\');" onmouseout="doMouseOut(\'' . $topic['id'] . '\');">' . $topic->title . '</a></li>';
		}
		print '</ul>';		
	
	}
	
	function printNPRPeople()
	{
		global $apiKey;
		
		$biosFeed = "http://api.npr.org/list?id=3007&apiKey=$apiKey";
		$allBios = curl_simplexml_load_file($biosFeed);
		print '<h2 class="nav"><a href="" onclick="return false;">People</a><span class="arrow">&gt;</span></h2>';
	
		if (array_key_exists('searchType', $_GET) && $_GET['searchType'] == 'People')
		{
			print '<ul class="nav" id="PeopleNav">';
		}
		else
		{
			print '<ul class="nav" id="PeopleNav" style="display:none;">';
		}		

		
		foreach ($allBios->subcategory as $subcat)
		{
			foreach ($subcat->item as $bio)
			{
				$title = str_replace('\'', '\\\'', $bio->title);
				print '<li><a href="" onclick="doSearch(\'' . $title . '\', \'People\');return false;" onmouseover="doMouseOver(this, \'' . $bio['id'] . '\', \'' . $title . '\');" onmouseout="doMouseOut(\'' . $bio['id'] . '\');">' . $bio->title . '</a></li>';
			}
		}	
		print '</ul>';	
	}	
	
	// This function tries to use the simplexml against a remote url
	// If this is disabled for security purposes, it then
	// uses CURL to download the xml and uses simplexml_load_string
	function curl_simplexml_load_file($URL)
	{
		$ret = @simplexml_load_file($URL);
		if ($ret != null)
		{
			return $ret;
		}		

		$ch = curl_init($URL);
		
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($ch, CURLOPT_HEADER, 0);
		
		$xml = simplexml_load_string(curl_exec($ch));
		
		curl_close($ch);
		
		return $xml;
	
	}

	// This function tries to use the get_headers against a remote url
	// If this is disabled for security purposes, it then
	// uses CURL to download the headers	
	function curl_get_headers($URL)
	{
		$ret = @get_headers($URL);
		if ($ret != null)
		{
			return $ret;
		}		
		
		$ch = curl_init();
		curl_setopt($ch, CURLOPT_URL, $URL);
		curl_setopt($ch, CURLOPT_HEADER, 1);
		curl_setopt($ch, CURLOPT_NOBODY, 0);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
		$headers = curl_exec ($ch);
		curl_close ($ch);
				
		return explode("\n", $headers);
	}

	// This function tries to use the file_get_contents against a remote url
	// If this is disabled for security purposes, it then
	// uses CURL to download the file and return it	
	function curl_file_get_contents($URL)
	{
		$ret = @file_get_contents($URL);
		if ($ret != null)
		{
			return $ret;
		}
		
		$ch = curl_init();
		$timeout = 5; // set to zero for no timeout
		curl_setopt ($ch, CURLOPT_URL, $URL);
		curl_setopt ($ch, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt ($ch, CURLOPT_CONNECTTIMEOUT, $timeout);
		$file_contents = curl_exec($ch);
		curl_close($ch);		

		return $file_contents;
	}
	
?>
