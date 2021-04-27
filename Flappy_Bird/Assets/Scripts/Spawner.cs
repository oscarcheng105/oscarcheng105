using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spawner : MonoBehaviour
{
    public float height;
    public float maxTime = 1f;
    private float timer = 0f;
    public GameObject pipe;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if(timer >= maxTime)
        {
            GameObject newPipe = Instantiate(pipe);
            newPipe.transform.position = transform.position + new Vector3(0, Random.Range(-height,height),0);
            Destroy(newPipe, 10f);
            timer = 0;
        }

        timer += Time.deltaTime;
    }
}
