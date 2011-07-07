package com.searchlocal.filereader;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.htmlparser.Node;
import org.htmlparser.NodeFilter;
import org.htmlparser.Parser;
import org.htmlparser.filters.NodeClassFilter;
import org.htmlparser.filters.OrFilter;
import org.htmlparser.nodes.TextNode;
import org.htmlparser.tags.TitleTag;
import org.htmlparser.util.NodeList;
import org.htmlparser.util.ParserException;

import com.searchlocal.bean.HtmlFileBean;
import com.searchlocal.exception.LogicException;
import com.searchlocal.util.CLogger;

/**
 * 
 * 
 */
public class HtmlReader {

	private static CLogger logger = new CLogger(HtmlReader.class);

	public List<HtmlFileBean> getHtmlFile(HtmlFileBean htmlBean) throws LogicException {

		String filepath = htmlBean.getPath();
		HtmlFileBean filebean = new HtmlFileBean();
		InputStream inputStream = null;
		StringBuffer sbStr = new StringBuffer();
		BufferedReader reader = null;
		List<HtmlFileBean> returnList = new ArrayList<HtmlFileBean>();
		String charset = getCharset(filepath);
		try {
			inputStream = new FileInputStream(filepath);
			reader = new BufferedReader(new InputStreamReader(inputStream, charset));
			String temp = "";
			while ((temp = reader.readLine()) != null) {
				if (!"".equals(temp)) {
					sbStr.append(temp);
				}
			}
			String result = sbStr.toString();
			filebean.setLastmodify(htmlBean.getLastmodify());
			filebean.setFilename(htmlBean.getFilename());
			filebean.setPath(filepath);
			filebean.setContent(readTextAndTitle(result, charset));
			returnList.add(filebean);
		} catch (FileNotFoundException e) {
			logger.error("LG_E001", filepath);
			throw new LogicException("LG_E001", e);
		} catch (UnsupportedEncodingException e) {
			logger.error("LG_E002", filepath);
			throw new LogicException("LG_E002", e);
		} catch (IOException e) {
			logger.error("LG_E003", filepath);
			throw new LogicException("LG_E003", e);
		} catch (ParserException e) {
			logger.error("LG_E004", filepath);
			throw new LogicException("LG_E004", e);
		} catch (Exception e) {
			logger.error("", filepath);
			throw new LogicException("", e);
		} finally {
			if (inputStream != null) {
				try {
					inputStream.close();
				} catch (IOException e) {
					throw new LogicException("LG_E003", e);
				}
			}
			if (reader != null) {
				try {
					reader.close();
				} catch (IOException e) {
					throw new LogicException("LG_E003", e);
				}
			}
		}
		return returnList;
	}

	//
	// /**
	// * 解析所有的节点
	// *
	// * @param result
	// * @throws Exception
	// */
	// public static String readAll(String result) throws Exception {
	// Parser parser;
	// parser = Parser.createParser(result, charset);
	// NodeFilter filter = new NodeClassFilter(Node.class);
	// NodeList list = parser.extractAllNodesThatMatch(filter);
	// String line = null;
	// // 读取所有的内容节点
	// StringBuffer bf = new StringBuffer();
	// for (int i = 0; i < list.size(); i++) {
	// Node textnode = (Node) list.elementAt(i);
	// line = textnode.toPlainTextString().trim();
	// if (line.length() == 0)
	// continue;
	// else {
	// bf.append(line);
	// }
	// }
	// return bf.toString();
	// }

	// /**
	// * 按页面方式处理.解析标准的html页面
	// *
	// * @param content
	// * @throws Exception
	// */
	// public static void readByHtml(String content) throws Exception {
	// Parser myParser;
	// myParser = Parser.createParser(content, charset);
	//
	// HtmlPage visitor = new HtmlPage(myParser);
	//
	// myParser.visitAllNodesWith(visitor);
	//
	// String textInPage = visitor.getTitle();
	// NodeList nodelist;
	// nodelist = visitor.getBody();
	// }

	// 读取文本内容和标题
	public static String readTextAndTitle(String result, String charset) throws Exception {
		Parser parser;
		NodeList nodelist;
		parser = Parser.createParser(result, charset);
		NodeFilter textFilter = new NodeClassFilter(TextNode.class);
		NodeFilter titleFilter = new NodeClassFilter(TitleTag.class);
		OrFilter lastFilter = new OrFilter();
		lastFilter.setPredicates(new NodeFilter[] { textFilter, titleFilter });
		nodelist = parser.parse(lastFilter);
		Node[] nodes = nodelist.toNodeArray();
		String line = "";
		StringBuffer bf = new StringBuffer();
		for (int i = 0; i < nodes.length; i++) {
			Node node = nodes[i];
			if (node instanceof TextNode) {
				TextNode textnode = (TextNode) node;
				line = textnode.getText();
			} else if (node instanceof TitleTag) {
				TitleTag titlenode = (TitleTag) node;
				line = titlenode.getTitle();
			}
			if (isTrimEmpty(line))
				continue;
			bf.append(line);
		}
		String reString = bf.toString();
		return reString;
	}

	//
	// // 分别读纯文本和链接
	//
	// public static void readTextAndLink(String result) throws Exception {
	// Parser parser;
	// NodeList nodelist;
	// parser = Parser.createParser(result, charset);
	// NodeFilter textFilter = new NodeClassFilter(TextNode.class);
	// NodeFilter linkFilter = new NodeClassFilter(LinkTag.class);
	// OrFilter lastFilter = new OrFilter();
	// lastFilter.setPredicates(new NodeFilter[] { textFilter, linkFilter });
	// nodelist = parser.parse(lastFilter);
	// Node[] nodes = nodelist.toNodeArray();
	// String line = "";
	// for (int i = 0; i < nodes.length; i++) {
	// Node node = nodes[i];
	// if (node instanceof TextNode) {
	// TextNode textnode = (TextNode) node;
	// line = textnode.getText();
	// } else if (node instanceof LinkTag) {
	// LinkTag link = (LinkTag) node;
	// line = link.getLink();
	// }
	// if (isTrimEmpty(line))
	// continue;
	// }
	// }

	public static String getCharset(String filepath) {
		InputStream inputStream = null;
		String charset = "";
		try {
			inputStream = new FileInputStream(filepath);
			BufferedReader reader = null;
			reader = new BufferedReader(new InputStreamReader(inputStream));
			String temp = "";

			String patternEncode = "((charset)\\s*=(\\s*))";
			Pattern p = Pattern.compile(patternEncode, Pattern.CASE_INSENSITIVE);

			while ((temp = reader.readLine()) != null) {
				if (!"".equals(temp)) {
					Matcher m = p.matcher(temp);
					while (m.find()) {
						int end = temp.indexOf("\"", m.end(0));
						if (end == -1) {
							end = temp.indexOf(">", m.end(0));
						}
						charset = temp.substring(m.end(0), end).toUpperCase();
						if ("".equals(charset)) {
							continue;
						} else {
							return charset;
						}
					}
				}
			}
		} catch (Exception e) {
			// TODO 注意消除资源(关闭I/O等)
			e.printStackTrace();
		}
		if ("".equals(charset)) {
			charset = "UTF-8";
		}
		return charset;
	}

	public static void main(String[] args) {
		// HtmlReader dd = new HtmlReader();
		// try {
		// System.out.println(dd.getHtmlFile("F:\\prject_back\\cronos_TONGQIHUA\\target\\war\\web\\HolidayTransfer\\work_and_man_hour_head.html"));
		// } catch (LogicException e) {
		// // TODO 注意消除资源(关闭I/O等)
		// e.printStackTrace();
		// }
	}

	/**
	 * 去掉左右空格后字符串是否为空
	 */
	public static boolean isTrimEmpty(String astr) {
		if ((null == astr) || (astr.length() == 0)) {
			return true;
		}
		if (isBlank(astr.trim())) {
			return true;
		}
		return false;
	}

	/**
	 * 字符串是否为空:null或者长度为0.
	 */
	public static boolean isBlank(String astr) {
		if ((null == astr) || (astr.length() == 0)) {
			return true;
		} else {
			return false;
		}
	}

}
