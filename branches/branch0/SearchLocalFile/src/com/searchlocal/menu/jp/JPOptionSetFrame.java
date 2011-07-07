package com.searchlocal.menu.jp;

import java.awt.Color;
import java.awt.Container;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.border.TitledBorder;
import javax.swing.filechooser.FileFilter;

import org.pushingpixels.substance.api.SubstanceLookAndFeel;
import org.pushingpixels.substance.api.skin.SubstanceBusinessBlackSteelLookAndFeel;

import com.searchlocal.constants.Constant;
import com.searchlocal.menu.CFrame;
import com.searchlocal.menu.CPanel;
import com.searchlocal.param.FileOpenerParam;
import com.searchlocal.util.FileOpenerUtil;
import com.searchlocal.util.MenuMessageUtil;
import com.searchlocal.util.RegistTableUtil;
import com.searchlocal.util.StringUtils;

public class JPOptionSetFrame extends CFrame implements ActionListener {

	private static final long serialVersionUID = 1L;

	static JPOptionSetFrame c;

	private static MenuMessageUtil msg = new MenuMessageUtil();

	private static String select = msg.getMsgbyId(Constant.button_select);

	private static String confirm = msg.getMsgbyId(Constant.button_confirm);

	private static String cancel = msg.getMsgbyId(Constant.button_cancel);

	private static String filefilterds = msg.getMsgbyId(Constant.file_filter_description);

	// select ie dir
	JFileChooser iedirchooser = new JFileChooser();

	JTextField iedir = new JTextField(60);

	// select word dir
	JFileChooser worddirchooser = new JFileChooser();

	JTextField worddir = new JTextField(60);

	// select excel dir
	JFileChooser exceldirchooser = new JFileChooser();

	JTextField exceldir = new JTextField(60);

	// select ppt dir
	JFileChooser pptdirchooser = new JFileChooser();

	JTextField pptdir = new JTextField(60);

	// select pdf dir
	JFileChooser pdfdirchooser = new JFileChooser();

	JTextField pdfdir = new JTextField(60);

	// select txt dir
	JFileChooser txtchooser = new JFileChooser();

	JTextField txtdir = new JTextField(60);

	public JPOptionSetFrame() {

		Container container = getContentPane();
		container.setLayout(null);
		setTitle(msg.getMsgbyId(Constant.title_setopenersoft));

		CPanel panel = new CPanel();
		panel.setLayout(null);
		panel.setBounds(5, 5, 480, 290);
		TitledBorder border = new TitledBorder("");
		border.setBorder(BorderFactory.createEtchedBorder(Color.orange, Color.BLUE));
		panel.setBorder(border);

		// discribtion
		panel.makeLabel(msg.getMsgbyId(Constant.label_setopenersoft), 60, 20, 190, 25);

		// IE DIR
		panel.makeLabel("IE:   ", 60, 40, 40, 25);
		iedir = panel.makeTextField(110, 40, 270, 20);
		iedir.setEditable(false);
		JButton selectiedirbotton = panel.makeButton(select, 390, 40, 60, 20, "");
		selectiedirbotton.putClientProperty(SubstanceLookAndFeel.BUTTON_NO_MIN_SIZE_PROPERTY,
				Boolean.TRUE);
		iedirchooser.addChoosableFileFilter(new ExeFilter());
		selectiedirbotton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				// TODO �Զ���ɷ�����?
				iedirchooser.setDialogTitle(filefilterds);
				int state = iedirchooser.showOpenDialog(null);
				File file = iedirchooser.getSelectedFile();
				if (file != null && state == JFileChooser.APPROVE_OPTION) {
					iedir.setText(file.getAbsolutePath());
				}
			}
		});

		// WORD DIR
		panel.makeLabel("WORD: ", 60, 70, 45, 25);
		worddir = panel.makeTextField(110, 70, 270, 20);
		worddir.setEditable(false);
		JButton selectworddirbotton = panel.makeButton(select, 390, 70, 60, 20, "");
		selectworddirbotton.putClientProperty(SubstanceLookAndFeel.BUTTON_NO_MIN_SIZE_PROPERTY,
				Boolean.TRUE);
		worddirchooser.addChoosableFileFilter(new ExeFilter());
		selectworddirbotton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				// TODO �Զ���ɷ�����?
				worddirchooser.setDialogTitle(filefilterds);
				int state = worddirchooser.showOpenDialog(null);
				File file = worddirchooser.getSelectedFile();
				if (file != null && state == JFileChooser.APPROVE_OPTION) {
					worddir.setText(file.getAbsolutePath());
				}
			}
		});

		// EXCEL DIR
		panel.makeLabel("EXCEL:", 60, 100, 45, 25);
		exceldir = panel.makeTextField(110, 100, 270, 20);
		exceldir.setEditable(false);
		JButton selectexceldirbotton = panel.makeButton(select, 390, 100, 60, 20, "");
		exceldirchooser.addChoosableFileFilter(new ExeFilter());
		selectexceldirbotton.putClientProperty(SubstanceLookAndFeel.BUTTON_NO_MIN_SIZE_PROPERTY,
				Boolean.TRUE);
		selectexceldirbotton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				// TODO �Զ���ɷ�����?
				exceldirchooser.setDialogTitle(filefilterds);
				int state = exceldirchooser.showOpenDialog(null);
				File file = exceldirchooser.getSelectedFile();
				if (file != null && state == JFileChooser.APPROVE_OPTION) {
					exceldir.setText(file.getAbsolutePath());
				}
			}
		});

		// PPT DIR
		panel.makeLabel("PPT:  ", 60, 130, 40, 25);
		pptdir = panel.makeTextField(110, 130, 270, 20);
		pptdir.setEditable(false);
		JButton selectpptdirbotton = panel.makeButton(select, 390, 130, 60, 20, "");
		pptdirchooser.addChoosableFileFilter(new ExeFilter());
		selectpptdirbotton.putClientProperty(SubstanceLookAndFeel.BUTTON_NO_MIN_SIZE_PROPERTY,
				Boolean.TRUE);
		selectpptdirbotton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				// TODO �Զ���ɷ�����?
				pptdirchooser.setDialogTitle(filefilterds);
				int state = pptdirchooser.showOpenDialog(null);
				File file = pptdirchooser.getSelectedFile();
				if (file != null && state == JFileChooser.APPROVE_OPTION) {
					pptdir.setText(file.getAbsolutePath());
				}
			}
		});

		// PDF DIR
		panel.makeLabel("PDF:  ", 60, 160, 40, 25);
		pdfdir = panel.makeTextField(110, 160, 270, 20);
		pdfdir.setEditable(false);
		JButton selectpdfdirbotton = panel.makeButton(select, 390, 160, 60, 20, "");
		pdfdirchooser.addChoosableFileFilter(new ExeFilter());
		selectpdfdirbotton.putClientProperty(SubstanceLookAndFeel.BUTTON_NO_MIN_SIZE_PROPERTY,
				Boolean.TRUE);
		selectpdfdirbotton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				// TODO �Զ���ɷ�����?
				pdfdirchooser.setDialogTitle(filefilterds);
				int state = pdfdirchooser.showOpenDialog(null);
				File file = pdfdirchooser.getSelectedFile();
				if (file != null && state == JFileChooser.APPROVE_OPTION) {
					pdfdir.setText(file.getAbsolutePath());
				}
			}
		});

		// TXT DIR
		panel.makeLabel("TXT:  ", 60, 190, 40, 25);
		txtdir = panel.makeTextField(110, 190, 270, 20);
		txtdir.setEditable(false);
		JButton selecttxtdirbotton = panel.makeButton(select, 390, 190, 60, 20, "");
		txtchooser.addChoosableFileFilter(new ExeFilter());
		selecttxtdirbotton.putClientProperty(SubstanceLookAndFeel.BUTTON_NO_MIN_SIZE_PROPERTY,
				Boolean.TRUE);
		selecttxtdirbotton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				txtchooser.setDialogTitle(filefilterds);
				int state = txtchooser.showOpenDialog(null);
				File file = txtchooser.getSelectedFile();
				if (file != null && state == JFileChooser.APPROVE_OPTION) {
					txtdir.setText(file.getAbsolutePath());
				}
			}
		});

		JButton confirmbutton = panel.makeButton(msg.getMsgbyId(Constant.button_confirm), 150, 230,
				80, 20, "");
		confirmbutton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				// TODO �Զ���ɷ�����?
				FileOpenerParam operparam = new FileOpenerParam();
				operparam.setExceldir(exceldir.getText());
				operparam.setIedir(iedir.getText());
				operparam.setPdfdir(pdfdir.getText());
				operparam.setTxtdir(txtdir.getText());
				operparam.setWorddir(worddir.getText());
				operparam.setPptdir(pptdir.getText());
				new FileOpenerUtil(operparam);
				c.setVisible(false);
			}
		});

		JButton cancelbutton = panel.makeButton(msg.getMsgbyId(Constant.button_cancel), 250, 230,
				80, 20, "");
		cancelbutton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				c.setVisible(false);
			}
		});

		String[] driver = new String[] { "C", "D", "E", "F", "G", "H", "I" };
		String iepath = ":\\Program Files\\Internet Explorer\\IEXPLORE.EXE";
		String officepath = RegistTableUtil.getExcelInstallRoot();
		String pdfpath = RegistTableUtil.getAdobeInstallRoot();
		String txtpath = ":\\WINDOWS\\system32\\notepad.exe";

		String excelexe = "EXCEL.EXE";
		String wordexe = "WINWORD.EXE";
		String pptexe = "POWERPNT.EXE";
		String pdfexe = "AcroRd32.exe";

		// word path
		String wordfilepath = officepath + wordexe;
		setChooser(wordfilepath, worddirchooser, worddir);

		// excel path
		String excelfilepath = officepath + excelexe;
		setChooser(excelfilepath, exceldirchooser, exceldir);

		// ppt path
		String pptfilepath = officepath + pptexe;
		setChooser(pptfilepath, pptdirchooser, pptdir);

		// pdf path
		String pdffilepath = pdfpath + File.separator + pdfexe;
		setChooser(pdffilepath, pdfdirchooser, pdfdir);

		for (int i = 0; i < driver.length; i++) {
			try {
				// ie path
				String iefilepath = driver[i] + iepath;
				setChooser(iefilepath, iedirchooser, iedir);

				// txt path
				String txtfilepath = driver[i] + txtpath;
				setChooser(txtfilepath, txtchooser, txtdir);
			} catch (Exception ex) {
				ex.printStackTrace();
			}
		}

		FileOpenerUtil openerUtil = new FileOpenerUtil(null);

		String word = openerUtil.getOpenerbyId("word");
		String excel = openerUtil.getOpenerbyId("excel");
		String ppt = openerUtil.getOpenerbyId("ppt");
		String pdf = openerUtil.getOpenerbyId("pdf");
		String txt = openerUtil.getOpenerbyId("txt");
		String ie = openerUtil.getOpenerbyId("ie");
		// 从配置文件里得到
		if (!StringUtils.isNull(word)) {
			setChooser(word, worddirchooser, worddir);
		}
		if (!StringUtils.isNull(excel)) {
			setChooser(excel, exceldirchooser, exceldir);
		}
		if (!StringUtils.isNull(ppt)) {
			setChooser(ppt, pptdirchooser, pptdir);
		}
		if (!StringUtils.isNull(pdf)) {
			setChooser(pdf, pdfdirchooser, pdfdir);
		}
		if (!StringUtils.isNull(txt)) {
			setChooser(txt, txtchooser, txtdir);
		}
		if (!StringUtils.isNull(ie)) {
			setChooser(ie, iedirchooser, iedir);
		}

		container.add(panel);
		this.setSize(500, 320);
		this.setLocationRelativeTo(null);
		this.setResizable(false);
	}

	public static void showframe() throws UnsupportedLookAndFeelException, ClassNotFoundException,
			InstantiationException, IllegalAccessException {
		JFrame.setDefaultLookAndFeelDecorated(true);
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				try {
					UIManager.setLookAndFeel(new SubstanceBusinessBlackSteelLookAndFeel());
				} catch (UnsupportedLookAndFeelException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				c = new JPOptionSetFrame();
				c.setIconImage(Toolkit.getDefaultToolkit().getImage(Constant.titleicopath));
				c.setVisible(true);
			}
		});
	}

	public void actionPerformed(ActionEvent e) {
	}

	class ExeFilter extends FileFilter {
		public boolean accept(File file) {
			return file.getName().toLowerCase().endsWith(".exe") || file.isDirectory();
		}

		public String getDescription() {
			return cancel;
		}
	}

	public static void main(String[] args) {
		try {
			JPOptionSetFrame frame = new JPOptionSetFrame();
			frame.showframe();
		} catch (UnsupportedLookAndFeelException e) {
			// TODO 自动生成 catch 部分
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO 自动生成 catch 部分
			e.printStackTrace();
		} catch (InstantiationException e) {
			// TODO 自动生成 catch 部分
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO 自动生成 catch 部分
			e.printStackTrace();
		}
	}

	private void setChooser(String path, JFileChooser fileChooser, JTextField field) {
		if (!path.equals("")) {
			File file = new File(path);
			if (file.exists()) {
				fileChooser.setSelectedFile(file);
				field.setText(path);
			}
		}
	}
}