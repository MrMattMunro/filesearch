/**
 * $RCSfile: IndexBeanList.java
 * $Revision: 1.0
 * $Date: Jan 1, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.lucene;

import java.io.IOException;
import java.util.Iterator;
import java.util.List;

import org.apache.lucene.document.DateTools;
import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field;
import org.apache.lucene.index.CorruptIndexException;
import org.apache.lucene.index.IndexWriter;

import com.searchlocal.bean.ChmFileBean;
import com.searchlocal.bean.ExcelFileBean;
import com.searchlocal.bean.HtmlFileBean;
import com.searchlocal.bean.PdfFileBean;
import com.searchlocal.bean.PptFileBean;
import com.searchlocal.bean.TxtFileBean;
import com.searchlocal.bean.WordFileBean;
import com.searchlocal.constants.Constant;

public class IndexBeanList {

	/**
	 * 生成索引文件
	 * 
	 * @return Returns the pool.
	 */
	public static void makeindex(String namespace, String doctype, List beanList) {

		IndexWriterFactory factory = new IndexWriterFactory();

		IndexWriter indexWriter = factory.getWriter(namespace);
		try {
			if (Constant.FileNameClassify.EXCEL.equals(doctype)) {
				for (Iterator itera = beanList.iterator(); itera.hasNext();) {
					ExcelFileBean bean = (ExcelFileBean) itera.next();
					makeExcelindex(indexWriter, bean);
				}
				factory.optimize(indexWriter);
			}
			if (Constant.FileNameClassify.WORD.equals(doctype)) {
				for (Iterator itera = beanList.iterator(); itera.hasNext();) {
					WordFileBean bean = (WordFileBean) itera.next();
					makeWordindex(indexWriter, bean);
				}
				factory.optimize(indexWriter);
			}
			if (Constant.FileNameClassify.PDF.equals(doctype)) {
				for (Iterator itera = beanList.iterator(); itera.hasNext();) {
					PdfFileBean bean = (PdfFileBean) itera.next();
					makePdfindex(indexWriter, bean);
				}
				factory.optimize(indexWriter);
			}
			if (Constant.FileNameClassify.PPT.equals(doctype)) {
				for (Iterator itera = beanList.iterator(); itera.hasNext();) {
					PptFileBean bean = (PptFileBean) itera.next();
					makePptindex(indexWriter, bean);
				}
				factory.optimize(indexWriter);
			}
			if (Constant.FileNameClassify.CHM.equals(doctype)) {
				for (Iterator itera = beanList.iterator(); itera.hasNext();) {
					ChmFileBean bean = (ChmFileBean) itera.next();
					makeChmindex(indexWriter, bean);
				}
				IndexWriterFactory.optimize(indexWriter);
			}
			if (Constant.FileNameClassify.HTML.equals(doctype)) {
				for (Iterator itera = beanList.iterator(); itera.hasNext();) {
					HtmlFileBean bean = (HtmlFileBean) itera.next();
					makeHtmlindex(indexWriter, bean);
				}
				factory.optimize(indexWriter);
			}
			if (Constant.FileNameClassify.TXT.equals(doctype)) {
				for (Iterator itera = beanList.iterator(); itera.hasNext();) {
					TxtFileBean bean = (TxtFileBean) itera.next();
					makeTxtindex(indexWriter, bean);
				}
				factory.optimize(indexWriter);
			}

			// 关闭IndexWriter
			if (indexWriter != null) {
				indexWriter.commit();
				indexWriter.close();
				factory.removeIndexWriter(namespace);
			}

		} catch (InterruptedException e) {
			// TODO 注意消除资源(关闭I/O等)
			e.printStackTrace();
		} catch (IOException e) {
			// TODO 注意消除资源(关闭I/O等)
			e.printStackTrace();
		}
	}

	public static void makeWordindex(IndexWriter indexWriter, WordFileBean bean)
			throws CorruptIndexException, IOException {
		Document document = new Document();
		document.add(new Field("paragraphNo", String.valueOf(bean.getParagraphNo()),
				Field.Store.YES, Field.Index.NO));

		document.add(new Field("filename", bean.getFilename(), Field.Store.YES,
				Field.Index.ANALYZED));
		document.add(new Field("path", bean.getPath(), Field.Store.YES, Field.Index.NOT_ANALYZED));
		document.add(new Field("content", bean.getContent(), Field.Store.YES, Field.Index.ANALYZED,
				Field.TermVector.WITH_POSITIONS_OFFSETS));

		document.add(new Field("lastmodify", DateTools.timeToString(bean.getLastmodify(),
				DateTools.Resolution.MINUTE), Field.Store.YES, Field.Index.NO));
		indexWriter.addDocument(document);
	}

	public static void makeExcelindex(IndexWriter indexWriter, ExcelFileBean bean)
			throws CorruptIndexException, IOException {
		Document document = new Document();
		document.add(new Field("sheetname", bean.getSheetname(), Field.Store.YES, Field.Index.NO));
		document.add(new Field("rownb", String.valueOf(bean.getRownb()), Field.Store.YES,
				Field.Index.NO));

		document.add(new Field("filename", bean.getFilename(), Field.Store.YES,
				Field.Index.ANALYZED));
		document.add(new Field("path", bean.getPath(), Field.Store.YES, Field.Index.NOT_ANALYZED));
		document.add(new Field("content", bean.getContent(), Field.Store.YES, Field.Index.ANALYZED,
				Field.TermVector.WITH_POSITIONS_OFFSETS));

		document.add(new Field("lastmodify", DateTools.timeToString(bean.getLastmodify(),
				DateTools.Resolution.MINUTE), Field.Store.YES, Field.Index.NO));
		indexWriter.addDocument(document);
	}

	public static void makePdfindex(IndexWriter indexWriter, PdfFileBean bean)
			throws CorruptIndexException, IOException {
		Document document = new Document();
		document.add(new Field("page", String.valueOf(bean.getPage()), Field.Store.YES,
				Field.Index.NO));

		document.add(new Field("filename", bean.getFilename(), Field.Store.YES,
				Field.Index.ANALYZED));
		document.add(new Field("path", bean.getPath(), Field.Store.YES, Field.Index.NOT_ANALYZED));
		document.add(new Field("content", bean.getContent(), Field.Store.YES, Field.Index.ANALYZED,
				Field.TermVector.WITH_POSITIONS_OFFSETS));

		document.add(new Field("lastmodify", DateTools.timeToString(bean.getLastmodify(),
				DateTools.Resolution.MINUTE), Field.Store.YES, Field.Index.NO));
		indexWriter.addDocument(document);
	}

	public static void makePptindex(IndexWriter indexWriter, PptFileBean bean)
			throws CorruptIndexException, IOException {
		Document document = new Document();
		document.add(new Field("page", String.valueOf(bean.getPage()), Field.Store.YES,
				Field.Index.NO));

		document.add(new Field("filename", bean.getFilename(), Field.Store.YES,
				Field.Index.ANALYZED));
		document.add(new Field("path", bean.getPath(), Field.Store.YES, Field.Index.NOT_ANALYZED));
		document.add(new Field("content", bean.getContent(), Field.Store.YES, Field.Index.ANALYZED,
				Field.TermVector.WITH_POSITIONS_OFFSETS));

		document.add(new Field("lastmodify", DateTools.timeToString(bean.getLastmodify(),
				DateTools.Resolution.MINUTE), Field.Store.YES, Field.Index.NO));
		indexWriter.addDocument(document);
	}

	public static void makeChmindex(IndexWriter indexWriter, ChmFileBean bean)
			throws CorruptIndexException, IOException {
		Document document = new Document();
		document.add(new Field("catalogname", bean.getCatalogname(), Field.Store.YES,
				Field.Index.NO));

		document.add(new Field("filename", bean.getFilename(), Field.Store.YES,
				Field.Index.ANALYZED));
		document.add(new Field("path", bean.getPath(), Field.Store.YES, Field.Index.NOT_ANALYZED));
		document.add(new Field("content", bean.getContent(), Field.Store.YES, Field.Index.ANALYZED,
				Field.TermVector.WITH_POSITIONS_OFFSETS));

		document.add(new Field("lastmodify", DateTools.timeToString(bean.getLastmodify(),
				DateTools.Resolution.MINUTE), Field.Store.YES, Field.Index.NO));
		indexWriter.addDocument(document);
	}

	public static void makeHtmlindex(IndexWriter indexWriter, HtmlFileBean bean)
			throws CorruptIndexException, IOException {
		Document document = new Document();

		document.add(new Field("filename", bean.getFilename(), Field.Store.YES,
				Field.Index.ANALYZED));
		document.add(new Field("path", bean.getPath(), Field.Store.YES, Field.Index.NOT_ANALYZED));
		document.add(new Field("content", bean.getContent(), Field.Store.YES, Field.Index.ANALYZED,
				Field.TermVector.WITH_POSITIONS_OFFSETS));

		document.add(new Field("lastmodify", DateTools.timeToString(bean.getLastmodify(),
				DateTools.Resolution.MINUTE), Field.Store.YES, Field.Index.NO));
		indexWriter.addDocument(document);
	}

	public static void makeTxtindex(IndexWriter indexWriter, TxtFileBean bean)
			throws CorruptIndexException, IOException {
		Document document = new Document();
		document.add(new Field("rownb", String.valueOf(bean.getRownb()), Field.Store.YES,
				Field.Index.NO));

		document.add(new Field("filename", bean.getFilename(), Field.Store.YES,
				Field.Index.ANALYZED));
		document.add(new Field("path", bean.getPath(), Field.Store.YES, Field.Index.NOT_ANALYZED));
		document.add(new Field("content", bean.getContent(), Field.Store.YES, Field.Index.ANALYZED,
				Field.TermVector.WITH_POSITIONS_OFFSETS));

		document.add(new Field("lastmodify", DateTools.timeToString(bean.getLastmodify(),
				DateTools.Resolution.MINUTE), Field.Store.YES, Field.Index.NO));
		indexWriter.addDocument(document);
	}
}
