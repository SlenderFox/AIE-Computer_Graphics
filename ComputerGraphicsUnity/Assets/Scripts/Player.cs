using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(CharacterController))]
[RequireComponent(typeof(Animator))]
public class Player : MonoBehaviour
{
    // The speed at which the player moves forward
    public float speed = 600;
    // How much force is imparted onto physics objects that are collided into
    public float pushPower = 15;

    // A reference to the character controller
    CharacterController controller = null;
    // A reference to the animator
    Animator animator = null;

    /// <summary>
    /// The start function is called once at boot
    /// </summary>
    void Start ()
    {
        // Properly references the character controller
        controller = GetComponent<CharacterController>();
        // Properly references the animator
        animator = GetComponent<Animator>();
    }

    /// <summary>
    /// Update is called once per frame
    /// </summary>
    void Update ()
    {
        // Gets wasd controls from the input class
        float vertical = Input.GetAxis("Vertical");
        float horizontal = Input.GetAxis("Horizontal");

        // If the player is not moving forward or backward, revert to idle animation
        if (vertical == 0)
            animator.Play("Idle");
        
        // Tells the character controller to move the player forward or backward
        controller.SimpleMove(transform.forward * vertical * speed * Time.deltaTime);
        // Tells the character controller to rotate the player left or right
        transform.Rotate(transform.up, horizontal * speed * 0.5f * Time.deltaTime);
        // Tells the animator to play the walking animation at a set speed
        animator.SetFloat("Speed", vertical * speed * Time.deltaTime);
    }

    /// <summary>
    /// Is called when a collision is detected
    /// </summary>
    /// <param name="hit">The object collided with</param>
    void OnControllerColliderHit (ControllerColliderHit hit)
    {
        // Gets the rigidbody of the object hit, if it does not have one or is kinematic return
        Rigidbody body = hit.collider.attachedRigidbody;
        if (body == null || body.isKinematic)
            return;

        // If the object hit is already moving away from the player return
        if (hit.moveDirection.y < -0.3F)
            return;

        // Applies a push force in the direction the object is moving
        Vector3 pushDir = new Vector3(hit.moveDirection.x, 0, hit.moveDirection.z);
        body.velocity = pushDir * pushPower;
    }
}