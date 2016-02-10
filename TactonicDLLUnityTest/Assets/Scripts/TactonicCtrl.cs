using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;
using System.Collections.Generic;

public class TactonicCtrl : MonoBehaviour {

	struct TactonicObj{
		public List<List<int>> lastFrame;
		public List<List<int>> curFrame;
		public int deviceCnt;
	};

	public GameObject framePlane;

	private int[] eachFrame;
	private float[,] eachFrameImg;
	private TactonicObj m_tactObj;

	private int[] nCount;
	private int[] nTotal;
	private int[] nDevice;

	private GameObject[] framePlanes;
	
	// for cpp plugin
//	[DllImport("TactonicDLL")]
//	static extern bool getPressUp(int index);

	//[DllImport("SimpleDLL")]
//	[DllImport("TactonicDLL")]
//	static extern bool getPressDown(int index);

//	[DllImport("SimpleDLL")]
//	static extern int getInt();

//	[DllImport("TactonicDLL")]
//	static extern bool getFrame (int[] frame, int[] nDevice, int[] nCount, int[] nTotal);

	[DllImport("SingleTactonicDLL")]
	static extern bool getMultiFrame (int[] frame, int[] nDevice, int[] nCount, int[] nTotal);

	[DllImport("SingleTactonicDLL")]
	static extern bool getSingleFrame (int[] frame, int[] nCount, int[] nTotal);

	// Use this for initialization
	void Start () {
		// test for only one panel
		eachFrame = new int[48 * 80 * 4];
		eachFrameImg = new float[2,48 * 80];
		m_tactObj.curFrame = new List<List<int>> ();
		m_tactObj.lastFrame = new List<List<int>> (48 * 80);
		List<int> tmp = new List<int>();
		for(int i = 0; i < 48 * 80; i++){
			tmp.Add(0);
		}
		for (int i = 0; i < 4; i++) {
			m_tactObj.curFrame.Add (tmp);
			m_tactObj.lastFrame.Add (tmp);
		}
		nCount = new int[1];
		nTotal = new int[1];
		nDevice = new int[1];

		framePlanes = new GameObject[8];
		for (int i = 0; i < framePlanes.Length; i++) {
			framePlanes [i] = Instantiate (framePlane, new Vector3(0,0,-10*i), Quaternion.identity) as GameObject;
			framePlanes[i].name = "frame" + i.ToString();
			framePlanes[i].GetComponent<Renderer>().enabled = false;
		}
	}

	// Update is called once per frame
	void Update () {
		//bool b = getPressDown (0);
		//Debug.Log (b);
		nCount [0] = 0;
		nTotal [0] = 0;
		nDevice [0] = 1;
		bool r = getMultiFrame (eachFrame, nDevice, nCount, nTotal);
		//bool r = getSingleFrame (eachFrame, nCount, nTotal);

		m_tactObj.deviceCnt = nDevice [0];
		//Debug.Log (r);
		Debug.Log ("nDevice:\t" + nDevice[0]);
		Debug.Log ("count:\t" + nCount[0]);
		Debug.Log ("total:\t" + nTotal[0]);

		for (int devIdx = 0; devIdx < nDevice[0]; devIdx ++) {
			int testtot = 0;
			for (int i = 0; i < 48 * 80; i++) {
				m_tactObj.curFrame[devIdx] [i] = eachFrame [i + devIdx * 48 * 80];
				eachFrameImg[devIdx,i] = (eachFrame [i + devIdx * 48 * 80] / 2000.0f);
				//if(eachFrame[i] != 0)
				//	Debug.Log(i / 80 + ":" + i % 80 + " is not empty");
				testtot += eachFrame [i + devIdx * 48 * 80];
			}
			Debug.Log("frame:" + devIdx + "\ttot:" + testtot);
			ExportAsImg (devIdx);
		}
		//int a = getInt ();
		//Debug.Log (a);

	}

	void ExportAsImg(int devIdx){
		// create a plane with prefab and assign img as texture
		// export data in current frame to image;
		Texture2D tex = new Texture2D(80, 48, TextureFormat.RGB24, false);

		Material mainMat = framePlanes[devIdx].GetComponent<Renderer> ().material;
		framePlanes[devIdx].GetComponent<Renderer>().enabled = true;
		Texture mainTex = mainMat.mainTexture;
		Debug.Log (mainTex.height);
//		int w = mainTex.width;

		var colors = new Color[48 * 80];
		for (int i = 0; i < 48 * 80; i++) {
			colors [i].r = eachFrameImg[devIdx,i];
			colors [i].g = eachFrameImg[devIdx,i];
			colors [i].b = eachFrameImg[devIdx,i];
			//colors[i].a = 1.0f;
			//colors[i] = Color.green;
		}
		//tex.LoadImage (eachFrameImg);
		tex.SetPixels (colors);
		tex.Apply( true );
		framePlanes[devIdx].GetComponent<Renderer>().material.mainTexture = tex;
	}
}
