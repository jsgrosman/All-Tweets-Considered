<?php
/*
 * Created on Jul 27, 2008 by Jason Grosman
 * This work is licensed under the Creative Commons Attribution-Noncommercial 3.0 Unported License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/3.0/ or send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
 *
 */

 	function getNewerUrl()
 	{
		if (array_key_exists('page', $_GET) && $_GET['page'] > 1)
		{
			$page = $_GET['page'];
			$thisUrl = $_SERVER['REQUEST_URI'];
			$thisUrl = preg_replace('/page=\d+/','page=' . ($page - 1), $thisUrl, 1, $count);
			if ($count == 0)
			{
				if (strpos($thisUrl, '?') > 0)
				{
					$thisUrl .= '&page=' . ($page - 1);
				}
				else
				{
					$thisUrl .= '?page=' . ($page - 1);
				}
			}
	
			return $thisUrl;
		} 
		else
 		{
 			return null;
 		}		
 	}
 	
 	function getOlderUrl()
 	{
 		$page = 1;
		if (array_key_exists('page', $_GET) && $_GET['page'] > 1)
		{
			$page = $_GET['page'];
		}
 		
		$thisUrl = $_SERVER['REQUEST_URI'];
		$thisUrl = preg_replace('/page=\d+/','page=' . ($page + 1), $thisUrl, 1, $count);
		if ($count == 0)
		{
			if (strpos($thisUrl, '?') > 0)
			{
				$thisUrl .= '&page=' . ($page + 1);
			}
			else
			{
				$thisUrl .= '?page=' . ($page + 1);
			}
			
			
		} 		
 		return $thisUrl;
 	}
 
 	function getFeedFromQuery()
 	{
 		global $resultsPerPage;
 		 		
 		if (array_key_exists('search', $_GET))
		{
			$twitterSearchValue = $_GET['search'];
		}
		else
		{
			$twitterSearchValue = 'npr';
		}
		
		if ($twitterSearchValue == 'All Things Considered')
		{
			$twitterSearchValue = '"' . $twitterSearchValue . '" OR ATC';
		}
		if ($twitterSearchValue == 'Wait Wait...Don\'t Tell Me!')
		{
			$twitterSearchValue = '"' . $twitterSearchValue . '" OR WWDTM';
		}
		if ($twitterSearchValue == 'Talk of the Nation')
		{
			$twitterSearchValue = '"' . $twitterSearchValue . '" OR TOTN';
		}
		if ($twitterSearchValue == 'Weekend Edition Saturday')
		{
			$twitterSearchValue = '"' . $twitterSearchValue . '" OR WESAT';
		}
		if ($twitterSearchValue == 'Weekend Edition Sunday')
		{
			$twitterSearchValue = '"' . $twitterSearchValue . '" OR WESUN';
		}
		if ($twitterSearchValue == 'Tell Me More')
		{
			$twitterSearchValue = '"' . $twitterSearchValue . '" NPR';
		}				
		
		$page = 1;
		if (array_key_exists('page', $_GET) && $_GET['page'] > 1)
		{
			$page = $_GET['page'];
		}

		$feed = 'http://search.twitter.com/search.json?q=+' . urlencode($twitterSearchValue) . '&rpp=' . $resultsPerPage . '&page=' . $page;	
		return $feed;
 		
 	}
 
	function printResult($item, $index)
	{
		// add links
		$content = preg_replace('/(http:\S+)\b/', '<a href="$1">$1</a>', $item->text);
		$content = preg_replace('/(@(\S+))\b/', '<a href="http://twitter.com/$2" target="_blank">$1</a>', $content);
		
		
		print '<div class="result">';
		print '<p class="tweet"><span class="tweetNum">#' . $index . '</span><a href="http://twitter.com/' . $item->from_user . '" target="_blank"><img class="avatar" height="48" width="48" src="' . $item->profile_image_url . '" alt=""/>';
		print '<span class="author">' . $item->from_user . '</a>:</span> ';
		print '<span class="content">' . html_entity_decode($content) . '</span>';		

		$twitterDate = strtotime($item->created_at);
		print('<br />');
		
		if (date('ymd') == date('ymd', $twitterDate))
		{
			print '<span class="twitterDate">Today at ' . date('g:i:s a', $twitterDate) . '</span>';
		}
		else
		{
			print '<span class="twitterDate">' . date('F jS, Y', $twitterDate) . ' at ' . date('g:i:s a', $twitterDate) . '</span>';
		}
		print '</p>';
		
	
	}
	
	
	function displayResultSet($feed)
	{
		global $apiKey;
		global $resultsPerPage;
		
		$twitterJson = curl_file_get_contents($feed);
		$twitterResults = json_decode($twitterJson);
		//print '<pre>' . print_r($twitterResults, true) . '</pre>';
		
		//return;

		$page = 1;
		if (array_key_exists('page', $_GET) && $_GET['page'] > 1)
		{
			$page = $_GET['page'];
		}
		
		$index = (($page - 1) * $resultsPerPage) + 1;
		foreach ($twitterResults->results as $item)
		{
			printResult($item, $index++);

			preg_match('/http:\S+\b/', $item->text, $matches);
			if (count($matches) > 0)
			{
				$twitterUrl = $matches[0];
				$headers = curl_get_headers($twitterUrl);
				if ($headers != null)
				{
					foreach ($headers as $headerElm)
					{
						if (preg_match('/^Location: (.*)$/i', $headerElm, $headerMatches))
						{
							$realUrl = urldecode($headerMatches[1]);
							error_log($realUrl);
							
							if (preg_match('/storyId=(\d+)/', $realUrl, $nprMatches))
							{
								$storyId = $nprMatches[1];
								$apiUrl = 'http://api.npr.org/query?id=' . $storyId . '&output=HTML&apiKey=' . $apiKey;
								print(curl_file_get_contents($apiUrl));
							}
	
							if (preg_match('/prgId=(\d+)/', $realUrl, $nprMatches))
							{
								$prgId = $nprMatches[1];
								$apiUrl = 'http://api.npr.org/query?id=' . $prgId . '&output=HTML&apiKey=' . $apiKey;
								print(curl_file_get_contents($apiUrl));
							}
						}
					}
				}
			}
			print '</div>';
		}
		
		if (count($twitterResults->results) == 0)
		{
				print '<h2 class="error">No Results Returned. Please try another search</h2>';
		}	
	}	
?>
