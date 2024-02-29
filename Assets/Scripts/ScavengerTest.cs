using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScavengerTest : MonoBehaviour
{
    float xAxis;
    float zAxis;
    Vector3 moveDir;
    [SerializeField] float moveSpeed;
    CharacterController controller;

    [SerializeField] float groundYOffset;
    [SerializeField] LayerMask groundMask;
    Vector3 spherePos;

    [SerializeField] float gravity = -9.81f;
    Vector3 velocity;

    Animator anim;

    // Start is called before the first frame update
    void Start()
    {
        controller = GetComponent<CharacterController>();
    }

    // Update is called once per frame
    void Update()
    {
        GetDirectionAndMove();
        Gravity();
    }

    void GetDirectionAndMove()
    {
        // wasdŰ����� x/z�� �Է¹ޱ�
        xAxis = Input.GetAxis("Horizontal");
        zAxis = Input.GetAxis("Vertical");

        // �밢�� �̵��� �̵��Ÿ��� �þ�� ������ ����ȭ
        moveDir = (transform.forward * zAxis + transform.right * xAxis).normalized;

        // �÷��̾� �̵�
        controller.Move(moveDir * moveSpeed * Time.deltaTime);
    }
    // �÷��̾ ���鿡 ��Ҵ��� Ȯ��
    bool IsGrounded()
    {
        spherePos = new Vector3(transform.position.x, transform.position.y - groundYOffset, transform.position.z);
        if (Physics.CheckSphere(spherePos, controller.radius - 0.05f, groundMask)) return true;
        return false;
    }

    // �߷� ����
    void Gravity()
    {
        if (!IsGrounded()) velocity.y += gravity * Time.deltaTime;
        else if (velocity.y < 0) velocity.y = -2;

        controller.Move(velocity * Time.deltaTime);
    }

    private void OnDrawGizmos()
    {
        Gizmos.color = Color.red;
        Gizmos.DrawWireSphere(spherePos, controller.radius - 0.05f);
    }
}
