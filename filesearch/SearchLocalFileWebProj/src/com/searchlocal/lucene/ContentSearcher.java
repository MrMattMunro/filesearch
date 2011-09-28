package com.web.searchlocal.lucene;

import java.io.File;
import java.io.IOException;
import java.io.StringReader;
import java.util.ArrayList;
import java.util.List;

import net.paoding.analysis.analyzer.PaodingAnalyzer;

import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.TokenStream;
import org.apache.lucene.analysis.ja.JapaneseAnalyzer;
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

import com.web.searchlocal.bean.BaseFileBean;
import com.web.searchlocal.constants.Constant;
import com.web.searchlocal.exception.LogicException;
import com.web.searchlocal.param.SearchParam;
import com.web.searchlocal.util.BeanUtil;
import com.web.searchlocal.util.StringUtil;

/**
 * 内容检索
 * 
 * <p>Title: 内容检索</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class ContentSearcher {

	/** 关键字所在的偏移量 */
	private static int CONTENTS_SHOW_LENGTH = 100;

	/**
	 * 根据关键字检索
	 * 
	 * @param param 检索参数
	 * @param indexlocal 检索根目录
	 * @throws LogicException
	 * @throws IOException
	 */
	public static List<BaseFileBean> queryAll(SearchParam param, String indexlocal)
			throws IOException, LogicException {
		// 取得文件类型
		String filetype = param.getSearchtype();
		List<BaseFileBean> returnList = new ArrayList<BaseFileBean>();
		if (Constant.ALL.equals(filetype)) {
			Analyzer analyzer = new PaodingAnalyzer();
			// Excel
			String excelIndexPath = indexlocal + File.separator + Constant.FileNameClassify.EXCEL;
			returnList.addAll(query(param, excelIndexPath, analyzer));
			// Word
			String wordIndexPath = indexlocal + File.separator + Constant.FileNameClassify.WORD;
			returnList.addAll(query(param, wordIndexPath, analyzer));
			// Pdf
			String pdfIndexPath = indexlocal + File.separator + Constant.FileNameClassify.PDF;
			returnList.addAll(query(param, pdfIndexPath, analyzer));
			// Ppt
			String pptIndexPath = indexlocal + File.separator + Constant.FileNameClassify.PPT;
			returnList.addAll(query(param, pptIndexPath, analyzer));
			// Html
			String htmlIndexPath = indexlocal + File.separator + Constant.FileNameClassify.HTML;
			returnList.addAll(query(param, htmlIndexPath, analyzer));
			// TXT
			String txtIndexPath = indexlocal + File.separator + Constant.FileNameClassify.TXT;
			returnList.addAll(query(param, txtIndexPath, analyzer));
			// Chm
			String chmIndexPath = indexlocal + File.separator + Constant.FileNameClassify.CHM;
			returnList.addAll(query(param, chmIndexPath, analyzer));
			
		    analyzer = new JapaneseAnalyzer(Version.LUCENE_33);
			// Excel
			excelIndexPath = indexlocal + File.separator
					+ Constant.FileNameClassify.EXCEL + File.separator
					+ "japanese";
			returnList.addAll(query(param, excelIndexPath, analyzer));
			// Word
			wordIndexPath = indexlocal + File.separator
					+ Constant.FileNameClassify.WORD + File.separator
					+ "japanese";
			returnList.addAll(query(param, wordIndexPath, analyzer));
			// Pdf
			pdfIndexPath = indexlocal + File.separator
					+ Constant.FileNameClassify.PDF + File.separator
					+ "japanese";
			returnList.addAll(query(param, pdfIndexPath, analyzer));
			// Ppt
			pptIndexPath = indexlocal + File.separator
					+ Constant.FileNameClassify.PPT + File.separator
					+ "japanese";
			returnList.addAll(query(param, pptIndexPath, analyzer));
			// Html
			htmlIndexPath = indexlocal + File.separator
					+ Constant.FileNameClassify.HTML + File.separator
					+ "japanese";
			returnList.addAll(query(param, htmlIndexPath, analyzer));
			// TXT
			txtIndexPath = indexlocal + File.separator
					+ Constant.FileNameClassify.TXT + File.separator
					+ "japanese";
			returnList.addAll(query(param, txtIndexPath, analyzer));
			// Chm
			chmIndexPath = indexlocal + File.separator
					+ Constant.FileNameClassify.CHM + File.separator
					+ "japanese";
			returnList.addAll(query(param, chmIndexPath, analyzer));
			
		} else {
			Analyzer analyzer = new PaodingAnalyzer();
			if (filetype.equals(Constant.FileNameClassify.EXCEL)) {
				// Excel
				String excelIndexPath = indexlocal + File.separator
						+ Constant.FileNameClassify.EXCEL;
				returnList.addAll(query(param, excelIndexPath, analyzer));
				
			    analyzer = new JapaneseAnalyzer(Version.LUCENE_33);
				// Excel
				excelIndexPath = indexlocal + File.separator
						+ Constant.FileNameClassify.EXCEL + File.separator
						+ "japanese";
				returnList.addAll(query(param, excelIndexPath, analyzer));
			}
			if (filetype.equals(Constant.FileNameClassify.WORD)) {
				// Word
				String wordIndexPath = indexlocal + File.separator + Constant.FileNameClassify.WORD;
				returnList.addAll(query(param, wordIndexPath, analyzer));
				
			    analyzer = new JapaneseAnalyzer(Version.LUCENE_33);
				// Word
				wordIndexPath = indexlocal + File.separator
						+ Constant.FileNameClassify.WORD + File.separator
						+ "japanese";
				returnList.addAll(query(param, wordIndexPath, analyzer));
			}
			if (filetype.equals(Constant.FileNameClassify.PDF)) {
				// Pdf
				String pdfIndexPath = indexlocal + File.separator + Constant.FileNameClassify.PDF;
				returnList.addAll(query(param, pdfIndexPath, analyzer));
				
				analyzer = new JapaneseAnalyzer(Version.LUCENE_33);
				// Pdf
				pdfIndexPath = indexlocal + File.separator
						+ Constant.FileNameClassify.PDF + File.separator
						+ "japanese";
				returnList.addAll(query(param, pdfIndexPath, analyzer));
			}
			if (filetype.equals(Constant.FileNameClassify.PPT)) {
				// Ppt
				String pptIndexPath = indexlocal + File.separator + Constant.FileNameClassify.PPT;
				returnList.addAll(query(param, pptIndexPath, analyzer));
				
			    analyzer = new JapaneseAnalyzer(Version.LUCENE_33);
			    
				// Ppt
				pptIndexPath = indexlocal + File.separator
						+ Constant.FileNameClassify.PPT + File.separator
						+ "japanese";
				returnList.addAll(query(param, pptIndexPath, analyzer));
			}
			if (filetype.equals(Constant.FileNameClassify.HTML)) {
				// Html
				String htmlIndexPath = indexlocal + File.separator + Constant.FileNameClassify.HTML;
				returnList.addAll(query(param, htmlIndexPath, analyzer));
				
				analyzer = new JapaneseAnalyzer(Version.LUCENE_33);
				
				// Html
				htmlIndexPath = indexlocal + File.separator
						+ Constant.FileNameClassify.HTML + File.separator
						+ "japanese";
				returnList.addAll(query(param, htmlIndexPath, analyzer));
			}
			if (filetype.equals(Constant.FileNameClassify.TXT)) {
				// TXT
				String txtIndexPath = indexlocal + File.separator + Constant.FileNameClassify.TXT;
				returnList.addAll(query(param, txtIndexPath, analyzer));
				
				analyzer = new JapaneseAnalyzer(Version.LUCENE_33);
				// TXT
				txtIndexPath = indexlocal + File.separator
						+ Constant.FileNameClassify.TXT + File.separator
						+ "japanese";
				returnList.addAll(query(param, txtIndexPath, analyzer));
			}
			if (filetype.equals(Constant.FileNameClassify.CHM)) {
				// Chm
				String chmIndexPath = indexlocal + File.separator + Constant.FileNameClassify.CHM;
				returnList.addAll(query(param, chmIndexPath, analyzer));
				
				analyzer = new JapaneseAnalyzer(Version.LUCENE_33);
				// Chm
				chmIndexPath = indexlocal + File.separator
						+ Constant.FileNameClassify.CHM + File.separator
						+ "japanese";
				returnList.addAll(query(param, chmIndexPath, analyzer));
			}
		}
		int startRow = param.getStartRow();
		int endRow = param.getEndRow();
		int size = returnList.size();
		endRow = endRow > size? size: endRow;
		return returnList.subList(startRow, endRow);
	}

	/**
	 * 根据关键字检索
	 * 
	 * @param param 检索参数
	 * @param indexpath 检索目录
	 * @throws LogicException
	 * @throws IOException
	 */
	public static List<BaseFileBean> query(SearchParam param, String indexpath, Analyzer analyzer) throws IOException,
			LogicException {
		File localFile = new File(indexpath);
		// 索引目录如不存在,则返回
		if (!localFile.exists()) {
			return new ArrayList<BaseFileBean>();
		}
		// 没有建立索引时
		File segMentFile = new File(indexpath + File.separator + "segments.gen");
		if ( !segMentFile.exists()){
			return new ArrayList<BaseFileBean>();
		}
		// 输入空串时
		String squery = param.getQuery();
		if (StringUtil.isNullString(squery)){
			return new ArrayList<BaseFileBean>();
		}
		
		FSDirectory fsd = SimpleFSDirectory.open(new File(indexpath));
		List<BaseFileBean> beanList = new ArrayList<BaseFileBean>();
		try {
			QueryParser parser = new QueryParser(Version.LUCENE_33, "content", analyzer);
			Query query;
			query = parser.parse(squery);

			TopScoreDocCollector collector = TopScoreDocCollector.create(100, true);
			IndexSearcher is = new IndexSearcher(fsd, true);
			is.search(query, collector);

			ScoreDoc[] scoreDoc = collector.topDocs().scoreDocs;

			SimpleHTMLFormatter simpleHTMLFormatter = new SimpleHTMLFormatter(
					"<font color=\"red\">", "</font>");

			Highlighter highlighter = new Highlighter(simpleHTMLFormatter, new QueryScorer(query));
			highlighter.setTextFragmenter(new SimpleFragmenter(CONTENTS_SHOW_LENGTH));

			if (scoreDoc.length == 0) {
				// System.out.println("result size ==0");
				// throw new
				// LogicException(msg.getMsgbyId(Constant.web_error_noresult),
				// "");
			}
			for (int i = 0; i < scoreDoc.length; i++) {
				Document document = is.doc(scoreDoc[i].doc);
				String content = document.get("content");
				String filename = document.get("filename");
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
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InvalidTokenOffsetsException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ParseException e) {
			e.printStackTrace();
		}
		return beanList;
	}

	/**
	 * 根据关键字检索
	 * 
	 * @param param 检索参数
	 * @param indexpath 检索目录
	 * @throws LogicException
	 * @throws IOException
	 * @throws LogicException 
	 */
	public static int getCount(SearchParam param, String indexlocal) throws IOException, LogicException {

		// 取得文件类型
		String filetype = param.getSearchtype();
		// 结果集总数
		int count = 0;
		if (Constant.ALL.equals(filetype)) {
			Analyzer analyzer = new PaodingAnalyzer();
			// Excel
			String excelIndexPath = indexlocal + File.separator + Constant.FileNameClassify.EXCEL;
			count = count + getCountByType(param, excelIndexPath, analyzer);
			// Word
			String wordIndexPath = indexlocal + File.separator + Constant.FileNameClassify.WORD;
			count = count + getCountByType(param, wordIndexPath, analyzer);
			// Pdf
			String pdfIndexPath = indexlocal + File.separator + Constant.FileNameClassify.PDF;
			count = count + getCountByType(param, pdfIndexPath, analyzer);
			// Ppt
			String pptIndexPath = indexlocal + File.separator + Constant.FileNameClassify.PPT;
			count = count + getCountByType(param, pptIndexPath, analyzer);
			// Html
			String htmlIndexPath = indexlocal + File.separator + Constant.FileNameClassify.HTML;
			count = count + getCountByType(param, htmlIndexPath, analyzer);
			// TXT
			String txtIndexPath = indexlocal + File.separator + Constant.FileNameClassify.TXT;
			count = count + getCountByType(param, txtIndexPath, analyzer);
			// Chm
			String chmIndexPath = indexlocal + File.separator + Constant.FileNameClassify.CHM;
			count = count + getCountByType(param, chmIndexPath, analyzer);
			
		    analyzer = new JapaneseAnalyzer(Version.LUCENE_33);
			// Excel
			excelIndexPath = indexlocal + File.separator
					+ Constant.FileNameClassify.EXCEL + File.separator
					+ "japanese";
			count = count + getCountByType(param, excelIndexPath, analyzer);
			// Word
			wordIndexPath = indexlocal + File.separator
					+ Constant.FileNameClassify.WORD + File.separator
					+ "japanese";
			count = count + getCountByType(param, wordIndexPath, analyzer);
			// Pdf
			pdfIndexPath = indexlocal + File.separator
					+ Constant.FileNameClassify.PDF + File.separator
					+ "japanese";
			count = count + getCountByType(param, pdfIndexPath, analyzer);
			// Ppt
			pptIndexPath = indexlocal + File.separator
					+ Constant.FileNameClassify.PPT + File.separator
					+ "japanese";
			count = count + getCountByType(param, pptIndexPath, analyzer);
			// Html
			htmlIndexPath = indexlocal + File.separator
					+ Constant.FileNameClassify.HTML + File.separator
					+ "japanese";
			count = count + getCountByType(param, htmlIndexPath, analyzer);
			// TXT
			txtIndexPath = indexlocal + File.separator
					+ Constant.FileNameClassify.TXT + File.separator
					+ "japanese";
			count = count + getCountByType(param, txtIndexPath, analyzer);
			// Chm
			chmIndexPath = indexlocal + File.separator
					+ Constant.FileNameClassify.CHM + File.separator
					+ "japanese";
			count = count + getCountByType(param, chmIndexPath, analyzer);
		} else {
			Analyzer analyzer = new PaodingAnalyzer();
			if (filetype.equals(Constant.FileNameClassify.EXCEL)) {
				// Excel
				String excelIndexPath = indexlocal + File.separator
						+ Constant.FileNameClassify.EXCEL;
				count = count + getCountByType(param, excelIndexPath, analyzer);
				
				analyzer = new JapaneseAnalyzer(Version.LUCENE_33);
				// Excel
				excelIndexPath = indexlocal + File.separator
						+ Constant.FileNameClassify.EXCEL + File.separator
						+ "japanese";
				count = count + getCountByType(param, excelIndexPath, analyzer);
			}
			if (filetype.equals(Constant.FileNameClassify.WORD)) {
				// Word
				String wordIndexPath = indexlocal + File.separator + Constant.FileNameClassify.WORD;
				count = count + getCountByType(param, wordIndexPath, analyzer);
				
				analyzer = new JapaneseAnalyzer(Version.LUCENE_33);
				// Excel
				wordIndexPath = indexlocal + File.separator + Constant.FileNameClassify.WORD + File.separator
						+ "japanese";
				count = count + getCountByType(param, wordIndexPath, analyzer);
			}
			if (filetype.equals(Constant.FileNameClassify.PDF)) {
				// Pdf
				String pdfIndexPath = indexlocal + File.separator + Constant.FileNameClassify.PDF;
				count = count + getCountByType(param, pdfIndexPath, analyzer);
				
				analyzer = new JapaneseAnalyzer(Version.LUCENE_33);
				// Excel
				pdfIndexPath = indexlocal + File.separator + Constant.FileNameClassify.PDF + File.separator
						+ "japanese";
				count = count + getCountByType(param, pdfIndexPath, analyzer);
			}
			if (filetype.equals(Constant.FileNameClassify.PPT)) {
				// Ppt
				String pptIndexPath = indexlocal + File.separator + Constant.FileNameClassify.PPT;
				count = count + getCountByType(param, pptIndexPath, analyzer);
				
				analyzer = new JapaneseAnalyzer(Version.LUCENE_33);
				// Excel
				pptIndexPath = indexlocal + File.separator + Constant.FileNameClassify.PPT + File.separator
						+ "japanese";
				count = count + getCountByType(param, pptIndexPath, analyzer);
			}
			if (filetype.equals(Constant.FileNameClassify.HTML)) {
				// Html
				String htmlIndexPath = indexlocal + File.separator + Constant.FileNameClassify.HTML;
				count = count + getCountByType(param, htmlIndexPath, analyzer);
				
				analyzer = new JapaneseAnalyzer(Version.LUCENE_33);
				// Excel
				htmlIndexPath = indexlocal + File.separator + Constant.FileNameClassify.HTML + File.separator
						+ "japanese";
				count = count + getCountByType(param, htmlIndexPath, analyzer);
			}
			if (filetype.equals(Constant.FileNameClassify.TXT)) {
				// TXT
				String txtIndexPath = indexlocal + File.separator + Constant.FileNameClassify.TXT;
				count = count + getCountByType(param, txtIndexPath, analyzer);
				
				analyzer = new JapaneseAnalyzer(Version.LUCENE_33);
				// Excel
				txtIndexPath = indexlocal + File.separator + Constant.FileNameClassify.TXT + File.separator
						+ "japanese";
				count = count + getCountByType(param, txtIndexPath, analyzer);
			}
			if (filetype.equals(Constant.FileNameClassify.CHM)) {
				// Chm
				String chmIndexPath = indexlocal + File.separator + Constant.FileNameClassify.CHM;
				count = count + getCountByType(param, chmIndexPath, analyzer);
				
				analyzer = new JapaneseAnalyzer(Version.LUCENE_33);
				// Excel
				chmIndexPath = indexlocal + File.separator + Constant.FileNameClassify.CHM + File.separator
						+ "japanese";
				count = count + getCountByType(param, chmIndexPath, analyzer);
			}
		}
		return count;
	}

	/**
	 * 取得某类文档的结果集条数
	 * 
	 * @param param 检索参数
	 * @param indexpath 文档类型的索引文件保存目录
	 * @throws LogicException
	 * @throws IOException
	 */
	public static int getCountByType(SearchParam param, String indexpath, Analyzer analyzer) throws IOException,
			LogicException {

		File localFile = new File(indexpath);
		int count = 0;
		// 索引目录如不存在,则返回
		if (!localFile.exists()) {
			return count;
		}
		// 没有建立索引时
		File segMentFile = new File(indexpath + File.separator + "segments.gen");
		if ( !segMentFile.exists()){
			return count;
		}
		// 输入空串时
		String squery = param.getQuery();
		if (StringUtil.isNullString(squery)){
			return count;
		}
		
		FSDirectory fsd = SimpleFSDirectory.open(localFile);
		try {
			// 查询
			QueryParser parser = new QueryParser(Version.LUCENE_33, "content", analyzer);
			Query query;
			query = parser.parse(param.getQuery());

			TopScoreDocCollector collector = TopScoreDocCollector.create(100, true);
			IndexSearcher is = new IndexSearcher(fsd, true);
			is.search(query, collector);
			ScoreDoc[] scoreDoc = collector.topDocs().scoreDocs;
			count = scoreDoc.length;
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ParseException e) {
			e.printStackTrace();
		}
		return count;
	}
	
}
