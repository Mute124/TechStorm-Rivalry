<?xml version="1.0" encoding="utf-8"?>
<file>
	<afflictions>
		<affliction>
			<name>Example Name</name>
			<tooltip>This is how you add afflictions!</tooltip>
			<!--0 = bad 1 = mixed-->
			<implication></implication>
			<severity></severity>
			<causes>
				<!--Put the damage type tag that can cause this here!-->
				<cause></cause>
			</causes>
			<!--What can treat this affliction?-->
			<treatments>
				<!--What heals the player of this affliction?-->
				<treatment></treatment>
			</treatments>
			<!--What does this affliction do?-->
			<affects>
				<affect>
					<!--What about the player gets affected?-->
					<targetcomponent></targetcomponent>
					<!--how much should be changed each affliction update?-->
					<changefactor></changefactor>
				</affect>
			</affects>
		</affliction>
	</afflictions>
</file>