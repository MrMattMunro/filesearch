package com.searchlocal.webcrawler.main;

import com.searchlocal.webcrawler.FetchAndProcessCrawler;

public class WebCrawlerMain {
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		FetchAndProcessCrawler crawler = new FetchAndProcessCrawler("C:/iWeb2/data/ch02", 2, 200);
		// crawler.setDefaultUrls(); 
		crawler.addUrl("http://www.slfile.net");
		crawler.addUrl("http://www.baidu.com");
		crawler.run(); 
	}

}
