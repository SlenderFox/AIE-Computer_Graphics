using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UiScript : MonoBehaviour
{
    // The force applied to the cube in the Z axis once it spawns
    public float m_fThrowForce;

    // A reference to the cube
    public GameObject m_goCube;
    // A reference to the empty game object the cube will spawn at
    public GameObject m_goSpawnPoint;

    /// <summary>
    /// Spawns a cube at a target location
    /// </summary>
    public void SpawnCube()
    {
        // Instantiates the cube
        GameObject newCube = Instantiate(m_goCube, m_goSpawnPoint.transform.position, m_goSpawnPoint.transform.rotation);
        // Applies force to the cube
        newCube.GetComponent<Rigidbody>().AddForce(new Vector3(0, 0, m_fThrowForce));
    }
}
