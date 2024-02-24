using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;
using Photon.Realtime;

public class PhotonManager : MonoBehaviourPunCallbacks
{
    // ����
    private readonly string version = "1.0f";
    // ����� ���̵�
    private string userId = "yongjae";

    void Awake()
    {
        // ���� ���� �����鿡�� �ڵ����� �� �ε�
        PhotonNetwork.AutomaticallySyncScene = true;
        // ���� ������ �������� ���� ���
        PhotonNetwork.GameVersion = version;
        // ���� ���̵� �Ҵ�
        PhotonNetwork.NickName = userId;
        // ���� ������ ��� Ƚ�� Ȯ��. �ʴ� 30ȸ
        Debug.Log(PhotonNetwork.SendRate);
        // ���� ����
        PhotonNetwork.ConnectUsingSettings();
    }

    // ���� ������ ���� �� ȣ��Ǵ� �ݹ� �Լ�
    public override void OnConnectedToMaster()
    {
        // �� ����ƴ��� Ȯ��
        Debug.Log("������ ���� ����");
        // �κ� �����ߴ��� Ȯ��, False
        Debug.Log($"�κ� ���� ���� = {PhotonNetwork.InLobby}");
        // �κ� ����
        PhotonNetwork.JoinLobby();
    }

    // �κ� ���� �� ȣ��Ǵ� �ݹ� �Լ�
    public override void OnJoinedLobby()
    {
        // �κ� �����ߴ��� Ȯ��, True
        Debug.Log($"�κ� ���� ���� = {PhotonNetwork.InLobby}");
        // �����Ǿ� �ִ� �� �߿��� �����ϰ� ����
        PhotonNetwork.JoinRandomRoom();
    }

    // ���� �� ���忡 �������� �� ȣ��Ǵ� �ݹ� �Լ�
    public override void OnJoinRandomFailed(short returnCode, string message)
    {
        // ���� �޼��� ���
        Debug.Log($"���� �� ���� ���� {returnCode}:{message}");

        // �� �Ӽ� ����
        RoomOptions ro = new RoomOptions();
        ro.MaxPlayers = 20;      // �ִ� ������ ��: 20��
        ro.IsOpen = true;        // ���� ���� ����
        ro.IsVisible = true;     // �κ񿡼� �� ��� ���� ����

        // �� ����
        PhotonNetwork.CreateRoom("My Room", ro);
    }

    // �� ������ �Ϸ�� �� ȣ��Ǵ� �ݹ� �Լ�
    public override void OnCreatedRoom()
    {
        Debug.Log("�� ���� ����");
        Debug.Log($"�� �̸� = {PhotonNetwork.CurrentRoom.Name}");
    }

    // �뿡 ������ �� ȣ��Ǵ� �ݹ� �Լ�
    public override void OnJoinedRoom()
    {
        Debug.Log($"�� ���� ���� = {PhotonNetwork.InRoom}");
        Debug.Log($"���� ���� �ο��� = {PhotonNetwork.CurrentRoom.PlayerCount}");
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
