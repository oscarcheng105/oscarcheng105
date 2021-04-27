using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Start : MonoBehaviour
{
    public Manager scene;
    void Update()
    {
        if(Input.GetKeyDown("space"))
        {
            scene.Replay();
        }
    }
}
