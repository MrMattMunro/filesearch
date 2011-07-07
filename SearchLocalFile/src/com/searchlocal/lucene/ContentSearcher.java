/**
 * $RCSfile: ContentSearcher.java
 * $Revision: 1.0
 * $Date: Jan 30, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.lucene;

import java.io.File;
import java.io.IOException;
import java.io.StringReader;
import java.util.ArrayList;
import java.util.List;

import net.paoding.analysis.analyzer.PaodingAnalyzer;

import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.TokenStream;
import org.apache.lucene.document.Document;
import org.apache.lucene.queryParser.ParseException;
import org.apache.lucene.queryParser.QueryParser;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.ScoreDoc;
import org.apache.lucene.search.TopScoreDocCollector;
import org.apache.lucene.search.highlight.Highlighter;
import org.apache.lucene.search.highlight.InvalidTokenOffsetsException;
import org.apache.lucene.search.highlight.QueryScorer;
import org.apache.lucene.search.highlight.SimpleFragmenter;
import org.apache.lucene.search.highlight.SimpleHTMLFormatter;
import org.apache.lucene.store.FSDirectory;
import org.apache.lucene.store.SimpleFSDirectory;
import org.apache.lucene.util.Version;

import com.searchlocal.bean.BaseFileBean;
import com.searchlocal.bean.ResultBean;
import com.searchlocal.exception.LogicException;
import com.searchlocal.param.SearchParam;
import com.searchlocal.util.BeanUtil;

/**
 * 搜索索引文件
 * 
 * <p>Title: 搜索索引文件</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class ContentSearcher {
	
	/** 文件块的长度 */
	private static int CONTENTS_SHOW_LENGTH = 100;
	
	
	/** 索引文件打开对象 */
	private static FSDirectory fsd = null;
	
	
	/** 索引文件打开对象 */
	private static IndexSearcher is = null;
	
	/** 
	 * 文件块的长度 
	 * 
	 * @param param 检索参数
	 * @param indexlocal 检索参数
	 * @return list 结果集列表
	 */
	public static List<ResultBean> query(SearchParam param)
			throws IOException, LogicException {
		// 索引文件保存目录
		String indexPath = param.getIndexPath();
		// 打开索引文件
		if(null == fsd){
			 fsd = SimpleFSDirectory.open(new File(indexPath));
		}
		List<ResultBean> beanList = new ArrayList<ResultBean>();
		try {
			// 生成KeyWord
			Analyzer analyzer = new PaodingAnalyzer();
			QueryParser parser = new QueryParser(Version.LUCENE_CURRENT, "content", analyzer);
			Query query;
			query = parser.parse(param.getKeyWord());
			
			TopScoreDocCollector collector = TopScoreDocCollector.create(100, true); 
			// 只加载一次
			if(null == is){
				is = new IndexSearcher(fsd, true); 
			}
			is.search(query, collector);   
				
			ScoreDoc[] scoreDoc = collector.topDocs().scoreDocs;

			SimpleHTMLFormatter simpleHTMLFormatter = new SimpleHTMLFormatter("<font color=\"red\">", "</font>"); 
			
			Highlighter highlighter = new Highlighter(simpleHTMLFormatter,  new QueryScorer(query));
			highlighter.setTextFragmenter(new SimpleFragmenter(CONTENTS_SHOW_LENGTH));

			if (scoreDoc.length == 0) {
				return beanList;
			}
			int startRow = param.getStartRow();
			int endRow = param.getEndRow();
			endRow = scoreDoc.length > endRow? endRow: scoreDoc.length;
			for (int i = startRow; i < endRow; i++) {
	            Document doc = is.doc(scoreDoc[i].doc);
				String content = doc.get("content");
				// 高亮显示
				TokenStream tokenStream = analyzer.tokenStream("content", new StringReader(content));
				content = highlighter.getBestFragment(tokenStream, content);
				ResultBean bean = BeanUtil.getBean(doc, content);
				beanList.add(bean);
			}
	    } catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InvalidTokenOffsetsException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}catch (ParseException e) {
			e.printStackTrace();
		}
		return beanList;
	}

	/** 
	 * 取得结果集的个数
	 * 
	 * @param param 检索参数
	 * @return int 结果集的个数
	 */
	public static int getCount(SearchParam param) throws IOException {
		// 索引文件保存目录
		String indexPath = param.getIndexPath();
		FSDirectory fsd = SimpleFSDirectory.open(new File(indexPath));
		int count = 0;
		try {
			// 分析内容
			Analyzer analyzer = new PaodingAnalyzer();
			QueryParser parser = new QueryParser(Version.LUCENE_CURRENT, "content", analyzer);
		
			// 关键字
			Query query = parser.parse(param.getKeyWord());
			
			TopScoreDocCollector collector = TopScoreDocCollector.create(100, true);   
			IndexSearcher is = new IndexSearcher(fsd, true);   
			is.search(query, collector);   
			ScoreDoc[] scoreDoc = collector.topDocs().scoreDocs;
			count = scoreDoc.length;
		} catch (ParseException e) {
			e.printStackTrace();
		}
		return count;
	}
}
