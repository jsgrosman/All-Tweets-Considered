<?php
/*
 * Created on Jul 27, 2008 by Jason Grosman
 * This work is licensed under the Creative Commons Attribution-Noncommercial 3.0 Unported License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/3.0/ or send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
 *
 */
	require_once "settings.inc";
	require_once "navigation.inc";
	require_once "twitterDisplay.inc";
	
	$feed = getFeedFromQuery();
?>


<html>
	<head>
		<title>All Tweets Considered</title>
		
		<style type="text/css" media="screen">@import "/alltweets/css/nprtwitter.css";</style>
		<script type="text/javascript">
			var apiKey = '<?php echo $apiKey; ?>';
		</script>	
		
		<script type="text/javascript" src="/alltweets/js/jquery-1.2.6.min.js"></script>
		<script type="text/javascript" src="/alltweets/js/nprtwitter.js"></script>
	</head>
	<body>
	
		<div id="header">
			<h1> All Tweets Considered : An NPR Twitter Browser </h1>
			<p>Developed using the <a href="http://www.npr.org/api">NPR API</a> and <a href="http://search.twitter.com">Twitter Search</a>. 
			You can see what NPR stories people on twitter are talking about, or search by NPR Program, Topic, Music Topic, or Person. This is definitely a work in progress, so expect things to improve over time.</p>
			<p>Technical details can be found <a href="http://www.jgrosman.com/jblog/?p=14">here</a>.</p>
			
			<form id="mainForm">
				<input type="hidden" id="searchField" name="search"></input>
				<input type="hidden" id="searchTypeField" name="searchType"></input>
			</form>	
		</div>
	
		<div id="main">
			<div id="bottom">
				<div id="leftcol">
					<ul id="menu">
					<h2 class="nav"><a href="" onclick="doSearch('NPR', '');return false;">Search all NPR</a></h2>
					<?php printNPRPrograms(); ?>
					<?php printNPRTopics(); ?>
					<?php printNPRPeople(); ?>
					</ul>
					<h4>Latest NPR News</h4>
					<script type="text/javascript" src="http://api.npr.org/query?id=1001&output=JS&apiKey=MDAwMTAwMDcwMDEyMTQ5MTAzNzAwOWI0Mw001"></script>
				</div>
				<div id="middlecol">
					<div class="resultsNav">
						<?php
							$newerUrl = getNewerUrl();
							$olderUrl = getOlderUrl();
						?>
						
						<?php
						if ($newerUrl != null)
						{
						?>
						<span class="newer"><a href="<?php echo $newerUrl; ?>">&lt;&lt; Newer</a></span>
						<?php
						}
						?>
						
						<span class="older"><a href="<?php echo $olderUrl; ?>">Older &gt;&gt;</a></span>
					</div>	
					<?php 
						displayResultSet($feed); 
					?>
					<div class="resultsNav">
						<?php
						if ($newerUrl != null)
						{
						?>
						<span class="newer"><a href="<?php echo $newerUrl; ?>">&lt;&lt; Newer</a></span>
						<?php
						}
						?>
						<span class="older"><a href="<?php echo $olderUrl; ?>">Older &gt;&gt;</a></span>
					</div>	
				</div>
			</div>
		
		
		</div>
	
	</body>
</html>		
		
