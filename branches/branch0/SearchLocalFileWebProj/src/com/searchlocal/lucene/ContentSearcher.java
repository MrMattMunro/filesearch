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
import com.searchlocal.exception.LogicException;
import com.searchlocal.param.SearchParam;
import com.searchlocal.util.BeanUtil;
import com.searchlocal.util.StringUtil;
import com.searchlocal.util.WebMessageUtil;

/**
 * This class is used to demonstrate the process of searching on an existing
 * Lucene index
 * 
 */
public class ContentSearcher {
	
	private static int CONTENTS_SHOW_LENGTH = 100;
	
	public static List query(SearchParam param, String indexlocal)
			throws IOException, LogicException {
		
		// This is the directory that hosts the Lucene index
		FSDirectory fsd = SimpleFSDirectory.open(new File(indexlocal));
		List<BaseFileBean> beanList = new ArrayList<BaseFileBean>();
		try {
			Analyzer analyzer = new PaodingAnalyzer();
			QueryParser parser = new QueryParser(Version.LUCENE_CURRENT, "content", analyzer);
			Query query;
			query = parser.parse(param.getQuery());
			
			TopScoreDocCollector collector = TopScoreDocCollector.create(100, true);   
			IndexSearcher is = new IndexSearcher(fsd, true);   
			is.search(query, collector);   
				
			ScoreDoc[] scoreDoc = collector.topDocs().scoreDocs;

			SimpleHTMLFormatter simpleHTMLFormatter = new SimpleHTMLFormatter("<font color=\"red\">", "</font>"); 
			
			Highlighter highlighter = new Highlighter(simpleHTMLFormatter,
					new QueryScorer(query));
			highlighter.setTextFragmenter(new SimpleFragmenter(CONTENTS_SHOW_LENGTH));

			int startRow = param.getStartRow();
			int endRow = param.getEndRow();

		    WebMessageUtil msg = new WebMessageUtil();
			if (scoreDoc.length == 0) {
				//System.out.println("result size ==0");
				//throw new LogicException(msg.getMsgbyId(Constant.web_error_noresult),  "");
			}
		
			String searchtype = param.getSearchtype();
			if ("all".equals(searchtype)) {
				for (int i = startRow; i < endRow; i++) {
		            Document doc = is.doc(scoreDoc[i].doc);
					String content = doc.get("content");
					// 高亮顯示
					TokenStream tokenStream = analyzer.tokenStream("content", new StringReader(content));
					content = highlighter.getBestFragment(tokenStream, content);
					BaseFileBean bean = BeanUtil.getBean(doc, content);
					beanList.add(bean);
				}
			} else {
				for (int i = 0; i < scoreDoc.length; i++) {
					Document document = is.doc(scoreDoc[i].doc); 
					String filename = document.get("filename");
					String suffixname = StringUtil.suffixName(filename);
					String type = StringUtil.getTypeBySuffixName(suffixname);
					if (searchtype.equals(type)) {
						String content = document.get("content");
						// 高亮顯示
						TokenStream tokenStream = analyzer.tokenStream("content", new StringReader(content));
						String nexcontent;
						nexcontent = highlighter.getBestFragment(tokenStream, content);
						if (nexcontent == null || nexcontent.equals("")) {
							nexcontent = content;
						}

						BaseFileBean bean = BeanUtil.getBean(document, nexcontent);
						beanList.add(bean);
					}
				}
				return beanList.subList(startRow, endRow);
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

	public static int getCount(SearchParam param, String indexlocal)
			throws IOException {
		// This is the directory that hosts the Lucene index
		FSDirectory fsd = SimpleFSDirectory.open(new File(indexlocal));
		int count = 0;
		try {
			Analyzer analyzer = new PaodingAnalyzer();
			QueryParser parser = new QueryParser(Version.LUCENE_CURRENT, "content", analyzer);
		
			Query query = parser.parse(param.getQuery());
			
			TopScoreDocCollector collector = TopScoreDocCollector.create(100, true);   
			IndexSearcher is = new IndexSearcher(fsd, true);   
			is.search(query, collector);   
				
			String searchtype = param.getSearchtype();

			ScoreDoc[] scoreDoc = collector.topDocs().scoreDocs;
			
			if ("all".equals(searchtype)) {
				count = scoreDoc.length;
			} else {
				int sum = 0;
				for (int i = 0; i < scoreDoc.length; i++) {
			        Document doc = is.doc(scoreDoc[i].doc);
					String filename = doc.get("filename");
					String suffixname = StringUtil.suffixName(filename);
					String type = StringUtil.getTypeBySuffixName(suffixname);
					if (searchtype.equals(type)) {
						sum++;
					}
				}
				count = sum;
			}

		} catch (ParseException e) {
			e.printStackTrace();
		}

		return count;
	}

}
