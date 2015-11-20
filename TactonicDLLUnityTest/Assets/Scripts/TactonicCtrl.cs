using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;

public class TactonicCtrl : MonoBehaviour {

	// for cpp plugin
	[DllImport("TactonicDLL")]
	static extern bool getPressUp(int index);

	//[DllImport("SimpleDLL")]
	[DllImport("TactonicDLL")]
	static extern bool getPressDown(int index);

	[DllImport("SimpleDLL")]
	static extern int getInt();

	// Use this for initialization
	void Start () {
	
	}

	// Update is called once per frame
	void Update () {
		bool b = getPressDown (0);
		Debug.Log (b);
		int a = getInt ();
		Debug.Log (a);
	}
}
