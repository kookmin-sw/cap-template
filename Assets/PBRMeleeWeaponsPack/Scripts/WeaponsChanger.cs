using UnityEngine;
using UnityEngine.UI;

namespace HQWeaponsPack
{
    public class WeaponsChanger : MonoBehaviour
    {
        [SerializeField]
        private Material[] m_ClothMaterials = null;

        [SerializeField]
        private AudioClip[] m_SwitchClip = null;

        [Space]

        [SerializeField]
        private KeyCode m_SwitchLeft = KeyCode.LeftArrow;

        [SerializeField]
        private KeyCode m_SwitchRight = KeyCode.RightArrow;

        [Space]

        [SerializeField]
        private Text m_WeaponNameTxt = null;

        [SerializeField]
        private Slider m_ClothSlider = null;

        private int m_SelectedWeapon = 0;

        private bool m_BloodEnabled = false;
        private bool m_ClothEnabled = false;

        private AudioSource m_AudioSource;
        private GameObject[] m_ClothObjects;
        private GameObject[] m_WeaponsList;


        private void Start()
        {
            m_ClothObjects = GameObject.FindGameObjectsWithTag("Cloth");
            m_AudioSource = GetComponent<AudioSource>();

            m_WeaponsList = GameObject.FindGameObjectsWithTag("Weapon");
            foreach (var weapon in m_WeaponsList)
            {
                weapon.transform.position = Vector3.zero;
                weapon.GetComponent<MeshRenderer>().material.EnableKeyword("_BloodAmount");
                weapon.SetActive(false);
            }

            m_WeaponsList[0].gameObject.SetActive(true);
            m_WeaponNameTxt.text = m_WeaponsList[0].name;
        }

        private void Update()
        {
            if (Input.GetKeyDown(m_SwitchLeft))
            {
                ChangeSelectedWeapon(-1);
            }
            else if (Input.GetKeyDown(m_SwitchRight))
            {
                ChangeSelectedWeapon(1);
            }
        }

        public void ChangeSelectedWeapon(int axis)
        {
            m_AudioSource.PlayOneShot(m_SwitchClip[Random.Range(0, m_SwitchClip.Length)]);

            m_WeaponsList[m_SelectedWeapon].SetActive(false);

            m_SelectedWeapon += axis;

            if (m_SelectedWeapon > m_WeaponsList.Length - 1)
            {
                m_SelectedWeapon = 0;
            }
            else if (m_SelectedWeapon < 0) m_SelectedWeapon = m_WeaponsList.Length - 1;

            m_WeaponsList[m_SelectedWeapon].SetActive(true);
            m_WeaponNameTxt.text = m_WeaponsList[m_SelectedWeapon].name;
        }

        public void ToggleBlood()
        {
            m_BloodEnabled = !m_BloodEnabled;

            foreach (var weapon in m_WeaponsList)
            {
                weapon.GetComponent<MeshRenderer>().material.SetFloat("_BloodAmount", m_BloodEnabled ? 0.9f : 0);
            }
        }

        public void ToggleCloth()
        {
            m_ClothEnabled = !m_ClothEnabled;

            foreach (GameObject cloth in m_ClothObjects)
            {
                cloth.SetActive(m_ClothEnabled);
            }
        }

        public void ChangeClothTextures()
        {
            for (int i = 0; i < m_ClothObjects.Length; i++)
            {
                m_ClothObjects[i].GetComponent<Renderer>().material = m_ClothMaterials[Mathf.CeilToInt(m_ClothSlider.value)];
            }
        }
    }
}
