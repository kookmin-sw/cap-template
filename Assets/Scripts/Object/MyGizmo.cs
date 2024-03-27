using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MyGizmo : MonoBehaviour
{
    public Color _color = Color.red;
    public float _radius = 0.1f;

    private void OnDrawGizmos()
    {
        // 기즈모 색상 설정
        Gizmos.color = _color;
        // 구 형태의 기즈모 생성
        Gizmos.DrawSphere(transform.position, _radius);
    }

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
