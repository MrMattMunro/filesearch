package com.searchlocal.util;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Properties;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.w3c.dom.Text;
import org.xml.sax.SAXException;

import com.searchlocal.constants.Constant;
import com.searchlocal.param.CreateNewParam;

public class XMLConfig {

	private static Document doc;

	/*
	 * use a path to create a XMLConfigUtil
	 */
	public XMLConfig() {

	}

	public void readXML(String configPath) {
		try {

			DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder builder = dbFactory.newDocumentBuilder();
			this.doc = builder.parse(new File(configPath));
		} catch (ParserConfigurationException e) {
			e.printStackTrace();
		} catch (SAXException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public List<CreateNewParam> getEntityList() {
		this.readXML(Constant.path + "com\\searchlocal\\properties\\searchers.xml");
		NodeList nodelist = doc.getElementsByTagName("searcher");

		List<CreateNewParam> entityList = new ArrayList<CreateNewParam>();
		for (int i = 0; i < nodelist.getLength(); i++) {
			Node node = nodelist.item(i);
			NodeList cnodeList = node.getChildNodes();
			CreateNewParam newparam = new CreateNewParam();
			for (int j = 0; j < cnodeList.getLength(); j++) {
				Node cnode = cnodeList.item(j);
				if (cnode.getNodeName().indexOf("indexpath") != -1) {
					newparam.setIndexpath(cnode.getTextContent().trim());
				}
				if (cnode.getNodeName().indexOf("searchpath") != -1) {
					newparam.setPath(cnode.getTextContent().trim());
				}
				if (cnode.getNodeName().indexOf("searchname") != -1) {
					newparam.setSearchname(cnode.getTextContent().trim());
				}
				if (cnode.getNodeName().indexOf("types") != -1) {
					List<String> typeList = Arrays.asList(cnode.getTextContent().split(","));
					newparam.setSelectfiletype(typeList);
				}
			}
			entityList.add(newparam);
		}
		return entityList;
	}

	public void removeXML(String searchname) {
		this.readXML(Constant.path + "com\\searchlocal\\properties\\searchers.xml");
		NodeList nodelist = this.doc.getElementsByTagName("searchname");
		for (int i = 0; i < nodelist.getLength(); i++) {
			Node node = nodelist.item(i);
			String nodevalue = node.getFirstChild().getNodeValue();
			if (nodevalue.equals(searchname)) {
				node.getParentNode().getParentNode().removeChild(node.getParentNode());
			}
		}
		this.writeFile();
	}

	public void writeXML(CreateNewParam newparam) {

		this.readXML(Constant.path + "com\\searchlocal\\properties\\searchers.xml");

		Element searcher = doc.createElement("searcher");
		String searchname = newparam.getSearchname();
		String searchpath = newparam.getPath();
		String indexpath = newparam.getIndexpath();

		List<String> selectfiletype = newparam.getSelectfiletype();
		StringBuffer temp = new StringBuffer();
		for (Object object : selectfiletype) {
			temp.append(object.toString() + ",");
		}
		String type = String.valueOf(temp.substring(0, temp.length() - 1));

		appendNode("searchname", searchname, searcher);
		appendNode("searchpath", searchpath, searcher);
		appendNode("indexpath", indexpath, searcher);
		appendNode("types", type, searcher);

		doc.getDocumentElement().appendChild(searcher);
		this.writeFile();
	}

	private void appendNode(String nodename, String nodetext, Element fathernode) {
		Text textseg;
		Element idexpathe = doc.createElement(nodename);
		textseg = doc.createTextNode(nodetext);
		idexpathe.appendChild(textseg);
		fathernode.appendChild(idexpathe);
	}

	private void writeFile() {
		TransformerFactory tFactory = TransformerFactory.newInstance();
		Transformer transformer;

		DOMSource source = new DOMSource(doc);

		File file = new java.io.File(Constant.path + "com\\searchlocal\\properties\\searchers.xml");
		StreamResult result = new StreamResult(file);

		try {
			transformer = tFactory.newTransformer();
			// ����XSLT���������(�ز�����,��������"��������")��
			Properties properties = transformer.getOutputProperties();
			properties.setProperty(OutputKeys.ENCODING, "UTF-8");
			transformer.setOutputProperties(properties);

			transformer.transform(source, result);

		} catch (TransformerConfigurationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (TransformerException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
