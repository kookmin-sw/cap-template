using UnityEngine;

namespace HQWeaponsPack
{
    public class SphericalRotation : MonoBehaviour
    {
        [SerializeField]
        private float m_RotationSpeed;

        private float m_MouseY;
        private float m_MouseX;

        private bool m_CanRotate;


        void Update()
        {
            if (Input.GetMouseButton(0))
            {
                m_CanRotate = true;
            }
            else m_CanRotate = false;

            RotateCamera();
        }

        void RotateCamera()
        {
            if (m_CanRotate)
            {
                m_MouseY = -Input.GetAxis("Mouse Y");
                m_MouseX = Input.GetAxis("Mouse X");
            }
            else
            {
                m_MouseY = 0;
                m_MouseX = 0;
            }

            transform.Rotate(m_RotationSpeed * Time.deltaTime * m_MouseY, m_RotationSpeed * Time.deltaTime * m_MouseX, 0);
        }
    }
}
