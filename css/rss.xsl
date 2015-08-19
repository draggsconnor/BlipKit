<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:dc="http://purl.org/dc/elements/1.1/">
<xsl:template match="/rss/channel">
<html>
<head>
	<title><xsl:value-of select="title"/></title>
	<meta charset="utf-8" />
	<meta name="viewport" content="width=device-width" />
	<link rel="stylesheet" href="css/main.css" />
</head>
<body>

<div class="main-wrapper">
	<header class="site-header">
		<div class="wrapper">
			<nav class="page-meta-nav">
				<ul>
					<li class="icon github"><a href="https://github.com/detomon" title="GitHub"><span class="monoxidicon circle-github"></span> <span class="title">GitHub</span></a></li>
					<li class="icon soundcloud"><a href="https://soundcloud.com/detomon" title="Soundcloud"><span class="monoxidicon circle-soudcloud"></span> <span class="title">Soundcloud</span></a></li>
				</ul>
			</nav>
			<div class="site-title">
				<a href="/">Monoxid</a>
			</div>
			<nav class="site-nav">
				<ul>
				</ul>
			</nav>
		</div>
	</header>
	<div class="page-content">
		<div class="wrapper">
			<div class="post-list">
				<xsl:for-each select="item">
					<article class="post">
						<h1 class="title"><a><xsl:attribute name="href"><xsl:value-of select="link"/></xsl:attribute><xsl:value-of select="title"/></a></h1>
						<div class="post-meta"><xsl:value-of select="pubDate"/></div>
						<div class="description"><xsl:value-of select="description" disable-output-escaping="yes"/></div>
					</article>
				</xsl:for-each>
			</div>
		</div>
		<div class="footer-push"></div>
	</div>
</div>

<footer class="site-footer">
	<div class="wrapper">
		<div class="footer-column"></div>
	</div>
</footer>

</body>
</html>
</xsl:template>
</xsl:stylesheet>
