using UnityEngine;

[CreateAssetMenu]
public class Item : ScriptableObject
{
    public string itemName;
    public Sprite itemImage;
    public GameObject itemPrefab; //아이템 원본 프리팹

    public int ItemType;
    public float ItemDamage;
    public float ItemRange;

}
