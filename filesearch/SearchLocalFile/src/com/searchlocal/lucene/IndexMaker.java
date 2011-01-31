package com.searchlocal.lucene;

import java.io.IOException;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

import org.apache.lucene.document.DateTools;
import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field;
import org.apache.lucene.index.CorruptIndexException;
import org.apache.lucene.index.IndexWriter;

import com.searchlocal.constants.Constant;
import com.searchlocal.dao.BaseDao;
import com.searchlocal.util.CLogger;
import com.searchlocal.util.SqlUtil;
import com.searchlocal.util.StringUtils;

/**
 * 索引新建操作类
 * 
 * <p>Title: 索引操作</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class IndexMaker {

	/** 日志 */
	private static CLogger logger = new CLogger(IndexMaker.class);

	/** Dao基类 */
	private static BaseDao dao = new BaseDao();

	/**
	 * 生成索引文件
	 * 
	 * @return Returns the pool.
	 */
	public static void makeindex(List doctypes, String indexpath, String namespace, Set<String> paths) throws Exception {

		IndexWriter indexWriter = IndexWriterFactory.getWriter(namespace);

		for (Iterator iter = doctypes.iterator(); iter.hasNext();) {
			String element = (String) iter.next();
			if ("excel".equals(element)) {
				// 取得连接
				Connection conn = dao.getConn(namespace);
				List<String> removeList = new ArrayList<String>();
				for (Iterator itera = paths.iterator(); itera.hasNext();) {
					String path = (String) itera.next();
					String type = StringUtils.getTypebyName(path);
					if (type.equals(Constant.FileNameClassify.EXCEL)) {
						String sql = SqlUtil.getsql(namespace, "selectExcelRecord");
						makeExcelindex(indexWriter, sql, path, conn);
						IndexWriterFactory.optimize(indexWriter);
						removeList.add(path);
					}
				}
				paths.removeAll(removeList);
				dao.closeConnection(null, null, conn);
			}
			if ("word".equals(element)) {
				// 取得连接
				Connection conn = dao.getConn(namespace);
				List<String> removeList = new ArrayList<String>();
				for (Iterator itera = paths.iterator(); itera.hasNext();) {
					String path = (String) itera.next();
					String type = StringUtils.getTypebyName(path);
					if (type.equals(Constant.FileNameClassify.WORD)) {
						String sql = SqlUtil.getsql(namespace, "selectWordRecord");
						makeWordindex(indexWriter, sql, path, conn);
						IndexWriterFactory.optimize(indexWriter);
						removeList.add(path);
					}
				}
				paths.removeAll(removeList);
				dao.closeConnection(null, null, conn);
			}
			if ("pdf".equals(element)) {
				// 取得连接
				Connection conn = dao.getConn(namespace);
				List<String> removeList = new ArrayList<String>();
				for (Iterator itera = paths.iterator(); itera.hasNext();) {
					String path = (String) itera.next();
					String type = StringUtils.getTypebyName(path);
					if (type.equals(Constant.FileNameClassify.PDF)) {
						String sql = SqlUtil.getsql(namespace, "selectPdfRecord");
						makePdfindex(indexWriter, sql, path, conn);
						IndexWriterFactory.optimize(indexWriter);
						removeList.add(path);
					}
				}
				paths.removeAll(removeList);
				dao.closeConnection(null, null, conn);
			}
			if ("ppt".equals(element)) {
				// 取得连接
				Connection conn = dao.getConn(namespace);
				List<String> removeList = new ArrayList<String>();
				for (Iterator itera = paths.iterator(); itera.hasNext();) {
					String path = (String) itera.next();
					String type = StringUtils.getTypebyName(path);
					if (type.equals(Constant.FileNameClassify.PPT)) {
						String sql = SqlUtil.getsql(namespace, "selectPptRecord");
						makePptindex(indexWriter, sql, path, conn);
						IndexWriterFactory.optimize(indexWriter);
						removeList.add(path);
					}
				}
				paths.removeAll(removeList);
				dao.closeConnection(null, null, conn);
			}
			if ("chm".equals(element)) {
				// 取得连接
				Connection conn = dao.getConn(namespace);
				List<String> removeList = new ArrayList<String>();
				for (Iterator itera = paths.iterator(); itera.hasNext();) {
					String path = (String) itera.next();
					String type = StringUtils.getTypebyName(path);
					if (type.equals(Constant.FileNameClassify.CHM)) {
						String sql = SqlUtil.getsql(namespace, "selectChmRecord");
						makeChmindex(indexWriter, sql, path, conn);
						IndexWriterFactory.optimize(indexWriter);
						removeList.add(path);
					}
				}
				paths.removeAll(removeList);
				dao.closeConnection(null, null, conn);
			}
			if ("html".equals(element)) {
				// 取得连接
				Connection conn = dao.getConn(namespace);
				List<String> removeList = new ArrayList<String>();
				for (Iterator itera = paths.iterator(); itera.hasNext();) {
					String path = (String) itera.next();
					String type = StringUtils.getTypebyName(path);
					if (type.equals(Constant.FileNameClassify.HTML)) {
						String sql = SqlUtil.getsql(namespace, "selectHtmlRecord");
						makeHtmlindex(indexWriter, sql, path, conn);
						IndexWriterFactory.optimize(indexWriter);
						removeList.add(path);
					}
				}
				paths.removeAll(removeList);
				dao.closeConnection(null, null, conn);
			}
			if ("txt".equals(element)) {
				// 取得连接
				Connection conn = dao.getConn(namespace);
				List<String> removeList = new ArrayList<String>();
				for (Iterator itera = paths.iterator(); itera.hasNext();) {
					String path = (String) itera.next();
					String type = StringUtils.getTypebyName(path);
					if (type.equals(Constant.FileNameClassify.TXT)) {
						String sql = SqlUtil.getsql(namespace, "selectTxtRecord");
						makeTxtindex(indexWriter, sql, path, conn);
						IndexWriterFactory.optimize(indexWriter);
						removeList.add(path);
					}
				}
				paths.removeAll(removeList);
				dao.closeConnection(null, null, conn);
			}
		}

		// 关闭IndexWriter
		if (indexWriter != null) {
			indexWriter.commit();
			indexWriter.close();
			IndexWriterFactory.removeIndexWriter(namespace);
		}
	}

	public static void makeWordindex(IndexWriter indexWriter, String sql, String path,
			Connection conn) throws Exception {
		ResultSet rs = dao.executeQuerySQL(sql, path, conn);
		while (rs.next()) {
			Document document = new Document();
			document.add(new Field("paragraphNo", rs.getString("paragraphNo"), Field.Store.YES,
					Field.Index.NO));

			addDcoument(document, rs, indexWriter);
		}
		rs.close();
	}

	public static void makeExcelindex(IndexWriter indexWriter, String sql, String path,
			Connection conn) throws Exception {
		ResultSet rs = dao.executeQuerySQL(sql, path, conn);
		while (rs.next()) {
			Document document = new Document();
			document.add(new Field("sheetname", rs.getString("sheetname"), Field.Store.YES,
					Field.Index.NO));
			document
					.add(new Field("rownb", rs.getString("rownb"), Field.Store.YES, Field.Index.NO));

			addDcoument(document, rs, indexWriter);
		}
		rs.close();
	}

	public static void makePdfindex(IndexWriter indexWriter, String sql, String path,
			Connection conn) throws Exception {
		ResultSet rs = dao.executeQuerySQL(sql, path, conn);
		while (rs.next()) {
			Document document = new Document();
			document.add(new Field("page", rs.getString("page"), Field.Store.YES, Field.Index.NO));
			addDcoument(document, rs, indexWriter);
		}
		rs.close();
	}

	public static void makePptindex(IndexWriter indexWriter, String sql, String path,
			Connection conn) throws Exception {
		ResultSet rs = dao.executeQuerySQL(sql, path, conn);
		while (rs.next()) {
			Document document = new Document();
			document.add(new Field("page", rs.getString("page"), Field.Store.YES, Field.Index.NO));
			addDcoument(document, rs, indexWriter);
		}
		rs.close();
	}

	public static void makeChmindex(IndexWriter indexWriter, String sql, String path,
			Connection conn) throws Exception {
		ResultSet rs = dao.executeQuerySQL(sql, path, conn);
		while (rs.next()) {
			Document document = new Document();
			document.add(new Field("catalogname", rs.getString("catalogname"), Field.Store.YES,
					Field.Index.NO));
			addDcoument(document, rs, indexWriter);
		}
		rs.close();
	}

	public static void makeHtmlindex(IndexWriter indexWriter, String sql, String path,
			Connection conn) throws Exception {
		ResultSet rs = dao.executeQuerySQL(sql, path, conn);
		while (rs.next()) {
			Document document = new Document();
			addDcoument(document, rs, indexWriter);
		}
		rs.close();
	}

	public static void makeTxtindex(IndexWriter indexWriter, String sql, String path,
			Connection conn) throws Exception {
		ResultSet rs = dao.executeQuerySQL(sql, path, conn);
		while (rs.next()) {
			Document document = new Document();
			document.add(new Field("rownb", StringUtils.replaceNull(rs.getString("rownb")),
					Field.Store.YES, Field.Index.NO));
			addDcoument(document, rs, indexWriter);
		}
		rs.close();
	}

	/**
	 * @param args
	 */
	public static void addDcoument(Document doc, ResultSet rs, IndexWriter indexWriter) {
		try {
			doc
					.add(new Field("filename", rs.getString("filename"), Field.Store.YES,
							Field.Index.NO));
			doc.add(new Field("path", rs.getString("path"), Field.Store.YES,
					Field.Index.NOT_ANALYZED));
			doc.add(new Field("content", rs.getString("content"), Field.Store.YES,
					Field.Index.ANALYZED, Field.TermVector.WITH_POSITIONS_OFFSETS));

			doc.add(new Field("lastmodify", DateTools.timeToString(rs.getTimestamp("lastmodify")
					.getTime(), DateTools.Resolution.MINUTE), Field.Store.YES, Field.Index.NO));

			indexWriter.addDocument(doc);
		} catch (CorruptIndexException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
