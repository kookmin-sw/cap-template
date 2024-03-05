using UnityEngine;

namespace HQWeaponsPack
{
    public class CameraMovement : MonoBehaviour
    {
        [SerializeField]
        private float m_ScrollSpeed;
        [SerializeField]
        private float m_MinDistance;
        [SerializeField]
        private float m_MaxDistance;

        private float m_CurrentPos;


        void Update()
        {
            float scroll = Input.GetAxis("Mouse ScrollWheel");
            Vector3 targetPosition = Vector3.forward * scroll * m_ScrollSpeed;

            //Move in constraints
            if (m_CurrentPos < m_MinDistance && scroll > 0)
            {
                MoveCamera(scroll, targetPosition);
            }
            if (m_CurrentPos > -m_MaxDistance && scroll < 0)
            {
                MoveCamera(scroll, targetPosition);
            }
        }

        void MoveCamera(float _scroll, Vector3 _targetPos)
        {
            m_CurrentPos += _scroll * m_ScrollSpeed;
            transform.Translate(_targetPos);
        }
    }
}
